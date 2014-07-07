#include <Ground.hpp>

Ground::Ground(const glm::vec2 &pos, const Cube &cube) : IEntity()
{
  _cube = cube;
  setPosition(glm::vec3(pos.x, 0, pos.y));
  _cube.translate(glm::vec3(_position));
}

Ground::~Ground()
{
  // TODO Auto-generated destructor stub
}

void    Ground::draw(Shader *shader)
{
  _cube.draw(shader);
}

void Ground::setRecourse(__attribute((unused)) const std::list<int> &recourse)
{
  _recourse = recourse;
}
