
#include "FontText.hpp"
#include "GameEngine.hpp"

bool checkCollision(glm::vec3 sphereCenter, float sphereRadius, glm::vec3 vA, glm::vec3 vB)
{
    glm::vec3 vDirToSphere = sphereCenter - vA;
    glm::vec3 vLineDir = glm::normalize(vB - vA);
    glm::vec3 vClosestPoint;

    float fLineLength = glm::distance(vA, vB);
    float t = glm::dot(vDirToSphere, vLineDir);

    if (t <= 0.0f)
        vClosestPoint = vA;
    else if (t >= fLineLength)
        vClosestPoint = vB;
    else
        vClosestPoint = vA + vLineDir* t;

    return (glm::distance(sphereCenter, vClosestPoint) <= sphereRadius);
}

int             read_from_server(t_selfd *fd)
{
    char        buff[BUFSIZ];
    int         r;
    size_t      size;

    r = 0;
    size = ring_buffer_left_write(fd->rbuff);
    size = (size < sizeof(buff)) ? size : sizeof(buff);
    if (size && ((r = read(fd->fd, buff, size)) > 0))
        write_buffer(fd->rbuff, buff, r);
    return (r);
}

std::string get_command(t_selfd *fd)
{
    char *cmd;
    size_t size;
    char buff[512];
    static std::string tmp("");
    std::string ret("");

    size = read_buffer(fd->rbuff, buff, sizeof(buff));
    if (size > 0 && ((cmd = static_cast<char *>(memchr(buff, '\n', size))))) {
        rollback_read_buffer(fd->rbuff, size - (cmd - buff + 1));
        buff[(cmd - buff)] = '\0';
        if (tmp != "") {
            ret = tmp + std::string(buff);
            tmp = std::string("");
            return ret;
        }
        return (std::string(buff));
    }
    else if (size > 0) {
        buff[size - 1] = '\0';
        tmp = std::string(buff);
    }
    return (ret);
}

GameEngine::GameEngine(float x, float y)
: _window(sf::VideoMode(x, y), WINDOW_NAME, sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(24, 0, 0, 3, 0)), _camera(x, y), _groundInfo(x, y), _playerInfo(x, y)
{
    _sizeX = x;
    _sizeY = y;
    _gem = NULL;
    _player = NULL;
    _mainShader = NULL;
    _textShader = NULL;
    _parser = NULL;
    _skybox = NULL;

    _window.setFramerateLimit(FPS);
}

GameEngine::~GameEngine()
{
    if (_gem != NULL)
    {
        _gem->destroyModel();
        delete _gem;
    }
    if (_player != NULL)
    {
        _player->destroyModel();
        delete _player;
    }
    if (_parser != NULL)
        delete _parser;
    if (_mainShader != NULL)
        delete _mainShader;
    if (_textShader != NULL)
        delete _textShader;
    if (_skybox != NULL)
        delete _skybox;
}

bool	GameEngine::initConnection(const std::string &host, const std::string &port)
{
    _client = create_connection(host.c_str(), port.c_str(), SOCK_STREAM, &connect);
    if (!_client)
        return (false);

    _elem = NULL;

    add_to_list(&_elem, static_cast<void *>(create_fd(_client->socket, NULL, (int (*)())(&handle_server))));

    _tv.tv_sec = 0;
    _tv.tv_usec = 1000;

    _gem = new Gem(LINEMATE);
    _player = new Player;
    _parser = new Parser(&_map, _gem, _player);

    do_select(_elem, &_tv, _parser);
    write(_client->socket, "GRAPHIC\n", 8);

    while (!_map.getSize().x || !_map.getSize().y)
      do_select(_elem, &_tv, _parser);
    return (true);
}

void	GameEngine::initOpenGL() const
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void	GameEngine::run()
{
    sf::Clock clock;

    Deads clarksToRemove;

    Rectangle toto(0, 0, 50, 50);

    toto.loadTexture("res/textures/broadcast.png");
    toto.build();

    _mainShader = new Shader("res/shaders/game.vert", "res/shaders/game.frag");
    _textShader = new Shader("res/shaders/text.vert", "res/shaders/text.frag");

    _skybox = new SkyBox;
    _pan = new Pan(_map.getSize());
    _pan->build();

    _mainShader->create();
    _textShader->create();

    _camera.setPos(glm::vec3(6.0f, 8.0f, 6.0f));
    _camera.setPointView(glm::vec3(0.1f, 0.1f, 0.1f));
    clock.restart();

    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                event.key.code == sf::Keyboard::Escape)
                _window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                selectObject(event.mouseButton.x, event.mouseButton.y);
            if (event.type == sf::Event::MouseWheelMoved)
                _camera.translate(glm::vec3(-event.mouseWheel.delta / 30.0f));
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        _camera.updateKeys();
        if (_camera.isFollowing())
            _camera.updateView();

        _camera.lookAt();

        _mainShader->bind();
        _mainShader->setUniform("gColor", glm::vec4(1));
        _mainShader->setUniform("camPos", _camera.getPos());
        _mainShader->setUniform("projection", _camera.getProjection());
        _mainShader->setUniform("view", _camera.getTransformation());
        _mainShader->setUniform("light", glm::vec4(0));

        _skybox->update(_camera.getPos());
        _skybox->draw(_mainShader);
        do_select(_elem, &_tv, _parser);

        _mainShader->setUniform("light", glm::vec4(0.1, 0.6, -0.1, 0));
        _mainShader->setUniform("ambientLight", glm::vec4(0.2, 0.2, 0.2, 1));

        if (_pan->getSize() != _map.getSize()) {
            _pan->scale(glm::vec3(_map.getSize().x / _pan->getSize().x, _map.getSize().y / _pan->getSize().y, 1));
            _pan->translate(glm::vec3((_map.getSize().x - _pan->getSize().x) / 2, 0, (_map.getSize().y - _pan->getSize().y) / 2));
            _pan->setSize(_map.getSize());
        }
        _pan->draw(_mainShader);

        for (Map::const_iterator it = _map.begin(), end = _map.end(); it != end; ++it) {
            (*it)->update(clock, _map.getTime() / 7);
            (*it)->draw(_mainShader);
        }
        for (Map::Players::iterator it = _map.playerBegin(), end = _map.playerEnd(); it != end; ++it) {
            (*it)->update(clock, _map.getTime() / 7);
            (*it)->draw(_mainShader);
            if ((*it)->getStatus() == Player::DEAD)
                clarksToRemove.push_back(it);
        }
        for (Map::Eggs::const_iterator it = _map.eggBegin(), end = _map.eggEnd(); it != end; ++it) {
            (*it)->update(clock, _map.getTime() / 7);
            (*it)->draw(_mainShader);
        }
        clock.restart();

        _textShader->bind();
        _textShader->setUniform("gColor", glm::vec4(1));
        _textShader->setUniform("projection", glm::ortho(0.0f, _sizeX, _sizeY, 0.0f, -1.0f, 1.0f));
        _textShader->setUniform("view", glm::mat4(1));

        if (_map.isResized())
        {
            _groundInfo.setGround(NULL);
            _playerInfo.setPlayer(NULL);
            _camera.follow(NULL);
            _map.setResized(false);
        }
        
        for (Map::Players::iterator it = _map.playerBegin(), end = _map.playerEnd(); it != end; ++it) {
            if ((*it)->isBroadcasting())
            {
                glm::vec2 temp = (*it)->getPosition();
                glm::vec3 broadcastPos = glm::project(glm::vec3(temp.x, 2.0f, temp.y), _camera.getTransformation(), _camera.getProjection(), glm::vec4(0, 0, _sizeX, _sizeY));
                (*it)->drawBroadcast(_textShader, broadcastPos, _sizeY);
            }
        }
        
        _groundInfo.update();
        if (_groundInfo.isVisible())
            _groundInfo.draw(_textShader);

        _playerInfo.update();
        if(_playerInfo.isVisible())
            _playerInfo.draw(_textShader);

        for (Deads::const_iterator it = clarksToRemove.begin(), end = clarksToRemove.end(); it != end; ++it) {
            _map.removePlayer(*it);
        }
        clarksToRemove.clear();
        _window.display();
    }
}

void		GameEngine::selectObject(int x, int y)
{
    int mouseX = x;
    int mouseY = _sizeY - y;

    glm::vec3 vA = glm::unProject(glm::vec3(mouseX, mouseY, 0.0f), _camera.getTransformation(), _camera.getProjection(), glm::vec4(0, 0, _sizeX, _sizeY));
    glm::vec3 vB = glm::unProject(glm::vec3(mouseX, mouseY, 1.0f), _camera.getTransformation(), _camera.getProjection(), glm::vec4(0, 0, _sizeX, _sizeY));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        for (Map::Players::iterator it = _map.playerBegin(), end = _map.playerEnd(); it != end; ++it)
        {
            if (checkCollision((*it)->getSphereCenter(), (*it)->getSphereRadius(), vA, vB))
            {
                _camera.follow(*it);
                _playerInfo.setPlayer((*it));
                _playerInfo.setVisible(true);
                return;
            }
        }
        _playerInfo.setVisible(false);
        _camera.follow(NULL);
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (Map::iterator it = _map.begin(), end = _map.end(); it != end; ++it)
        {
            if (checkCollision((*it)->getSphereCenter(), (*it)->getSphereRadius(), vA, vB))
            {
                _groundInfo.setGround((*it));
                _groundInfo.setVisible(true);
                return;
            }
        }
        _groundInfo.setVisible(false);
    }
}

int handle_server(t_selfd *fd, void *parser)
{
    std::string cmd;
    int r;
    ssize_t swr;
    Parser *cpy = static_cast<Parser *>(parser);

    if (ISREADABLE(fd))
    {
        if (((r = read_from_server(fd)) < 0 && errno != EINTR) || (r == 0))
            return (-1);
    }
    //  if (ISWRITEABLE(fd) && (r = write_to_client(fd)) < 0 && errno != EINTR)
    //    return (-1);
    while ((cmd = get_command(fd)) != "")
    {
        cpy->parseCmd(cmd);
    }
    swr = ring_buffer_left_read(fd->wbuff);
    if (!swr && fd->to_close)
        return (-1);
    if (swr)
        CHECKWRITE(fd);
    CHECKREAD(fd);
    return (0);
}
