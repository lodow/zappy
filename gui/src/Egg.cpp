#include "Egg.hpp"

Egg::Egg() : _model(new Model)
{
  //TODO _model->loadObj("PATH1", "PAHT2");
}

Egg::Egg(const Egg &egg, const glm::vec2 &pos, size_t nb)
: _pos(pos), _model(new Model(*egg._model)), _nb(nb)
{
  _model->translate(glm::vec3(_pos.x, 0.5f, _pos.y));
}

Egg::~Egg()
{
  delete _model;
}

void Egg::draw(Shader *shader) const
{
  shader->setUniform("gColor", glm::vec4(1, 1, 1, 1));
  shader->setUniform("ambientLight", glm::vec4(0.1, 0.1, 0.1, 1));
  //TODO initialize model before draw !
  //_model->draw(shader);
}

void Egg::update(__attribute__((unused)) const sf::Clock &clock,
    __attribute__((unused)) float serverSpeed)
{

}

void Egg::setRecourse(__attribute__((unused)) const std::list<int> &recourse)
{

}

void Egg::setPosition(const glm::vec2 &pos)
{
  _pos = pos;
}

const std::list<int> &Egg::getRecourse() const
{
  return _recourse;
}

const glm::vec2 &Egg::getPosition() const
{
  return _pos;
}

size_t Egg::getNb() const
{
  return _nb;
}

void Egg::setNb(size_t nb)
{
  _nb = nb;
}
