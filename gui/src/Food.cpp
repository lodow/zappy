
#include "utils.hpp"
#include "Food.hpp"

Food::Food()
{
    _model = new Model;
    _model->loadObj("res/models/food/apple.obj", "res/models/food/apple.png");
}

Food::Food(const Food &food, const glm::vec2 &pos)
{
    _model = new Model(*food._model);
    _pos = pos;

    _pos.x += ((rand() % 6) / 10.0f) - 0.25f;
    _pos.y += ((rand() % 6) / 10.0f) - 0.25f;

    _model->translate(glm::vec3(_pos.x, 0.5f, _pos.y));

    _sphereRadius = 0.3f;
    _sphereCenter = _model->getPos();
}

Food::~Food()
{
    delete _model;
}

void Food::draw(Shader *shader) const
{
    shader->setUniform("gColor", glm::vec4(1, 1, 1, 1));
    shader->setUniform("ambientLight", glm::vec4(0.1, 0.1, 0.1, 1));
    _model->draw(shader);
}

void Food::update(const sf::Clock &clock, UNUSED float serverSpeed)
{
    _model->rotate(glm::vec3(0, 1, 0), 1.0f * clock.getElapsedTime().asMilliseconds());
}

void Food::setRecourse(UNUSED const std::list<int> &recourse)
{

}

const std::list<int> &Food::getRecourse() const
{
    return (_recourse);
}

void Food::setPosition(const glm::vec2 &pos)
{
    _pos = pos;
}

const glm::vec2 &Food::getPosition() const
{
    std::cout << "Food" << std::endl;
    return _pos;
}

const glm::vec3	&Food::getSphereCenter() const
{
    return (_sphereCenter);
}

const float		Food::getSphereRadius() const
{
    return (_sphereRadius);
}
