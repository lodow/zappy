#ifndef IENTITY_HPP_
# define IENTITY_HPP_

class IEntity
{
public:
  virtual ~IEntity() {};
  virtual void draw(sf::RenderWindow &window) const = 0;
  virtual const sf::Vector2i &getPos() const = 0;
};

#endif /* IENTITY_HPP_ */
