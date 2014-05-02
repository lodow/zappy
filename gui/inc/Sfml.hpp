#ifndef SFML_HPP_
# define SFML_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/OpenGL.hpp>
# include <list>
# include "utils.hpp"

# define WINDOW_NAME	"ZAPPY"
# define FONT_PATH	"Monospace.ttf"
# define REFRESH_RATE	100
# define BLACK		sf::Color::Black
# define WHITE		sf::Color::White

typedef std::list<sf::Text> TextList;

class Sfml {
private:
  sf::RenderWindow	_window;
  sf::Font		_font;
  sf::Thread		_thread;
  TextList		_texts;

public:
  Sfml(const int&, const int&);
  ~Sfml();
  void	run();
  void	waitThread();
  void	putText(const std::string &text, const int &x, const int &y,
		const int &size, const sf::Color color);

};

void	launch_sfml(Sfml *sfml);

#endif /* !SFML_HPP_ */
