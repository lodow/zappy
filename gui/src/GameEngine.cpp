#include "GameEngine.hpp"

int             read_from_server(t_selfd *fd)
{
  char          buff[BUFSIZ];
  int           r;
  size_t        size;

  r = 0;
  size = ring_buffer_left_write(fd->rbuff);
  size = (size < sizeof(buff)) ? size : sizeof(buff);
  if (size && ((r = read(fd->fd, buff, size)) > 0))
    write_buffer(fd->rbuff, buff, r);
  return (r);
}

std::string                    get_command(t_selfd *fd)
{
  char                  *cmd;
  size_t                size;
  char                  buff[512];

  size = read_buffer(fd->rbuff, buff, sizeof(buff));
  if (size && ((cmd = static_cast<char *>(memchr(buff, '\n', size))))) {
      rollback_read_buffer(fd->rbuff, size - (cmd - buff + 1));
      buff[(cmd - buff)] = '\0';
      return (std::string(buff));
  }
  return (std::string(""));
}

GameEngine::GameEngine(const int &x, const int &y) :
  _window(sf::VideoMode(x, y), WINDOW_NAME) {

  /* Init connexion */
  _client = create_connection("::1", "4242", SOCK_STREAM, &connect_nb);
  if (!_client)
    return ;
  int status;
  std::cout << "Connecting . ";
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
  _tv.tv_usec = 100000;
  _parser = new Parser(&_map);
  do_select(_elem, &_tv, _parser);
  write(_client->socket, "GRAPHIC\n", 8);

  _map.push_back(new FontText(sf::Vector2i(50, 50), "Bonjour Fabulus!", 12, sf::Color::Black));
  _map.push_back(new FontText(sf::Vector2i(50, 100), "Bonjour Fabulus!", 12, sf::Color::Black));
  _parser = new Parser(&_map);
  this->run();
}

GameEngine::~GameEngine() {
  delete _parser;
}

void	GameEngine::run() {
  sf::Texture texture;
  if (!texture.loadFromFile("res/sprites/zizou.jpg"))
    return ;
  sf::Sprite sprite;
  sprite.setTexture(texture);

  while (_window.isOpen()) {
      sf::Event event;
      while (_window.pollEvent(event)) {
	if (event.type == sf::Event::Closed ||
	    event.key.code == sf::Keyboard::Escape)
	  _window.close();
      }
      _window.clear();
      do_select(_elem, &_tv, _parser);
      _window.draw(sprite);
      for (Map::iterator it = _map.begin(), end = _map.end(); it != end; ++it) {
	(*it)->draw(_window);
      }
      sf::sleep(sf::milliseconds(REFRESH_RATE));
      _window.display();
    }
}

int handle_server(t_selfd *fd, void *parser)
{
  std::string cmd;
  int r;
  ssize_t swr;
  Parser *cpy = static_cast<Parser *>(parser);

  if (ISREADABLE(fd)) {
      if (((r = read_from_server(fd)) < 0 && errno != EINTR) || (r == 0))
	return (-1);
  }
//  if (ISWRITEABLE(fd) && (r = write_to_client(fd)) < 0 && errno != EINTR)
//    return (-1);
  while ((cmd = get_command(fd)) != "")
    cpy->parseCmd(cmd);
  swr = ring_buffer_left_read(fd->wbuff);
  if (!swr && fd->to_close)
    return (-1);
  if (swr)
    CHECKWRITE(fd);
  CHECKREAD(fd);
  return (0);
}
