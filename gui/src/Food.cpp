#include "Food.hpp"

Food::Food()
{
  _model = new Model;
  _model->loadObj("res/models/food/bucket.obj", "res/models/food/bucket.png");
}

Food::Food(const Food &food, const glm::vec2 &pos)
{
  _model = new Model(*food._model);
  _pos = pos;
  _model->translate(glm::vec3(_pos.x, 0.5f, _pos.y));
}

Food::~Food()
{
  delete _model;
}

void Food::draw(Shader *shader)
{
  shader->setUniform("gColor", glm::vec4(1, 1, 1, 1));
  _model->draw(shader);
}

void Food::setRecourse(__attribute__((unused)) const std::list<int> &recourse)
{

}

void Food::setPosition(const glm::vec2 &pos)
{
  _pos = pos;
}

const glm::vec2 &Food::getPosition() const
{
  return _pos;
}
