#ifndef FONTTEXT_HPP_
# define FONTTEXT_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/OpenGL.hpp>
# include "IEntity.hpp"

# define FONT_PATH	"res/font/Monospace.ttf"

class FontText : public IEntity
{
public:
  FontText(const sf::Vector2i &pos, const std::string &msg, int size, sf::Color color);
  virtual ~FontText();
  virtual void draw(sf::RenderWindow &window) const;
  virtual const sf::Vector2i &getPos() const;


private:
  sf::Text _text;
  sf::Font _font;
  sf::Vector2i _pos;
};

#endif /* FONTTEXT_HPP_ */
