#include "Sfml.hpp"

Sfml::Sfml(const int &x, const int &y) :
  _window(sf::VideoMode(x, y), WINDOW_NAME), _thread(&launch_sfml, this) {

  if (!_font.loadFromFile(FONT_PATH)) {
    //TODO throw exception
    std::cerr << "Error on font.loadFromFile" << std::endl;
  }

  _thread.launch();
}

Sfml::~Sfml() {

}

/*
** Lance le thread principale de la lib
*/

void	launch_sfml(Sfml *sfml) {
  sfml->run();
}

/*
** Boucle principale de la sfml (le refresh tous REFRESH_RATE ms)
*/

void	Sfml::run() {
  while (_window.isOpen())
    {
      sf::Event event;
      while (_window.pollEvent(event)) {
	if (event.type == sf::Event::Closed ||
	    event.key.code == sf::Keyboard::Escape)
	  _window.close();
      }
      _window.clear();
      for (TextList::iterator it = _texts.begin(); it != _texts.end(); ++it)
	_window.draw(*it);
      sf::sleep(sf::milliseconds(REFRESH_RATE));
      _window.display();
    }
}

void	Sfml::waitThread() {
  _thread.wait();
}

/*
** Rajoute un element sf::text dans la list _texts qui sera ensuite afficher dans la boucle principale
*/

void		Sfml::putText(const std::string &msg, const int &x, const int &y,
		      const int &size, const sf::Color color) {
  sf::Text	text;

  text.setFont(_font);
  text.setString(msg);
  text.setCharacterSize(size);
  text.setColor(color);
  text.setPosition(x, y);
  _texts.push_back(text);
}
