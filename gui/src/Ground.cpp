#include <Ground.hpp>

Ground::Ground(const glm::vec2 &pos, const Cube &cube, const Gem &gem) : _gem(gem), _position(pos)
{
  _cube = cube;
  _cube.translate(glm::vec3(_position.x, 0, _position.y));
  _gem.setPosition(_position);
  for (int i = 0; i < 6; ++i) {
      _gemList.push_back(new Gem(_gem, static_cast<GemType>(i), _position));
  }
}

Ground::~Ground()
{
  // TODO Auto-generated destructor stub
}

void    Ground::draw(Shader *shader)
{
  _cube.draw(shader);
  for (GemList::const_iterator it = _gemList.begin(), end = _gemList.end(); it != end; ++it) {
      (*it)->draw(shader);
  }
}

void Ground::setRecourse(__attribute((unused)) const std::list<int> &recourse)
{
  _recourse = recourse;
}

const glm::vec2 &Ground::getPosition() const {
  return _position;
}

void Ground::setPosition(const glm::vec2 &pos) {
  _position = pos;
}
