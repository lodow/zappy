
#include "SkyBox.hpp"
#include "Pan.hpp"
#include "GameEngine.hpp"

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
    std::string ret;
    
    size = read_buffer(fd->rbuff, buff, sizeof(buff));
    if (size && ((cmd = static_cast<char *>(memchr(buff, '\n', size))))) {
        rollback_read_buffer(fd->rbuff, size - (cmd - buff + 1));
        buff[(cmd - buff)] = '\0';
        if (tmp != "") {
            ret = tmp + std::string(buff);
            tmp = std::string("");
            return ret;
        }
        return (std::string(buff));
    }
    else if (size) {
        buff[size] = 0;
        tmp = std::string(buff);
    }
    return (std::string(""));
}

GameEngine::GameEngine(const int &x, const int &y)
: _window(sf::VideoMode(x, y), WINDOW_NAME, sf::Style::Default, sf::ContextSettings(32, 8, 0, 3, 0))
{
    _window.setFramerateLimit(FPS);
    
    //    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    //    glBlendFunc(GL_ONE, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    _gem = new Gem(LINEMATE);
    _cube = new Cube;
    _cube->build();
    _cube->loadTexture("res/textures/grass.png");
    
    /* Init connexion */
    _client = create_connection("127.0.0.1", "4242", SOCK_STREAM, &connect_nb);
    if (!_client)
        return ;
    int status;
    std::cout << "Connecting . " << std::endl;
    while ((status = is_connected(_client)) == 1) {
        usleep(500);
        std::cout << ".";
    }
    if (status == -1) {
        std::cerr << "Error on connection" << std::endl;
        return ;
    }
    _elem = NULL;
    
    add_to_list(&_elem, static_cast<void *>(create_fd(_client->socket, NULL, (int (*)())(&handle_server))));
    
    _tv.tv_sec = 0;
    _tv.tv_usec = 1000;
    
    _parser = new Parser(&_map, _cube, _gem);
    
    do_select(_elem, &_tv, _parser);
    write(_client->socket, "GRAPHIC\n", 8);
    do_select(_elem, &_tv, _parser);

    run();
}

GameEngine::~GameEngine()
{
    _cube->destroyGeometry();
    _gem->destroyGeometry();
    
    delete _parser;
    delete _cube;
    delete _gem;
}

void	GameEngine::run() {
    
    Shader 	*shader = new Shader("res/shaders/game.vert", "res/shaders/game.frag");
    Camera 	camera;
    sf::Clock clock;
    SkyBox 	skybox;
    Pan 	pan(glm::vec2(10, 10));
    
    shader->create();
    
    camera.setPos(glm::vec3(6.0f, 8.0f, 6.0f));
    camera.setPointView(glm::vec3(0.1f, 0.1f, 0.1f));
    clock.restart();
    pan.build();
    pan.scale(glm::vec3(10, 10, 1));

    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                event.key.code == sf::Keyboard::Escape)
                _window.close();
            if (event.type == sf::Event::MouseWheelMoved)
                camera.translate(glm::vec3(-event.mouseWheel.delta / 50.0f));
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            camera.translate(glm::vec3(-0.1, 0, -0.1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            camera.translate(glm::vec3(0.1, 0, 0.1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            camera.translate(glm::vec3(-0.1, 0, 0.1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            camera.translate(glm::vec3(0.1, 0, -0.1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            camera.translate(glm::vec3(0.1, 0.1, 0.1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            camera.translate(glm::vec3(-0.1, -0.1, -0.1));
        
//        camera.update(event.key.code);
        camera.lookAt();
        
        shader->bind();
        shader->setUniform("gColor", glm::vec4(1, 1, 1, 1));
        shader->setUniform("camPos", camera.getPos());
        shader->setUniform("projection", camera.getProjection());
        shader->setUniform("view", camera.getTransformation());
        shader->setUniform("light", glm::vec4(0));
        
        skybox.draw(shader, camera.getPos());
        
        shader->setUniform("light", glm::vec4(0.1, 0.6, -0.1, 0));
        shader->setUniform("ambientLight", glm::vec4(0.2, 0.2, 0.2, 1));
        
        do_select(_elem, &_tv, _parser);
        
        shader->setUniform("gColor", glm::vec4(1, 1, 1, 1));
        pan.draw(shader);
        
        for (Map::iterator it = _map.begin(), end = _map.end(); it != end; ++it)
            (*it)->draw(shader);
        for (Map::Players::iterator it = _map.playerBegin(), end = _map.playerEnd(); it != end; ++it) {
            (*it)->update(clock);
            (*it)->draw(shader);
        }
        
        shader->setUniform("ambientLight", glm::vec4(0.5, 0.5, 0.5, 1));
        
        _window.display();
        clock.restart();
    }
    delete shader;
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
