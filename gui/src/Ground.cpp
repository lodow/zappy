#include "Ground.hpp"

Ground::Ground(const sf::Vector2i &pos) : _pos(pos)
{

}

Ground::~Ground()
{

}

void Ground::draw(__attribute__((unused)) sf::RenderWindow &window) const
{
  //window.draw(_text);
}

const sf::Vector2i &Ground::getPos() const
{
  return _pos;
}
