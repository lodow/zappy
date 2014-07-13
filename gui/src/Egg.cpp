
#include "utils.hpp"
#include "Egg.hpp"

Egg::Egg() : _model(new Model)
{
    _model->loadObj("res/models/egg/egg.obj", "res/models/egg/egg.png");
}

Egg::Egg(const Egg &egg, const glm::vec2 &pos, size_t nb)
: _pos(pos), _model(new Model(*egg._model)), _nb(nb)
{
    _model->translate(glm::vec3(_pos.x, 0.5f, _pos.y));
}

Egg::~Egg()
{

}

void Egg::draw(Shader *shader) const
{
    shader->setUniform("gColor", glm::vec4(1, 1, 1, 1));
    _model->draw(shader);
}

void Egg::update(UNUSED const sf::Clock &clock,
                 UNUSED float serverSpeed)
{
    _model->rotate(glm::vec3(0, 1, 0), 1.0f);
}

void Egg::setRecourse(UNUSED const std::list<int> &recourse)
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
