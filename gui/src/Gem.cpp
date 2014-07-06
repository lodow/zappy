
#include "Gem.hpp"

Gem::Gem()
{
    _model = new Model;
    _model->loadObj("res/models/gem.obj", "res/models/gem.png");
    _model->translate(glm::vec3(0, 0.5, 0));
}

Gem::Gem(const Gem &gem)
{
    _model = new Model(*gem._model);
}

Gem::~Gem()
{
    
}

void	Gem::draw(Shader *shader)
{
    shader->setUniform("fColor", glm::vec4(1, 0, 0, 0.3));
    _model->draw(shader);
}