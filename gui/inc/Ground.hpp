#ifndef GROUND_HPP_
# define GROUND_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/OpenGL.hpp>
# include "IEntity.hpp"

class Ground : public IEntity
{
public:
  Ground(const sf::Vector2i &pos);
  virtual ~Ground();
  virtual void draw(sf::RenderWindow &window) const;
  virtual const sf::Vector2i &getPos() const;

private:
  sf::Vector2i _pos;
};

#endif /* GROUND_HPP_ */
