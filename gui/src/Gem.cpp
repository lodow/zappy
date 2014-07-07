
#include "Gem.hpp"

uint64_t cpu_cycle(){
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

Gem::Gem(GemType type)
: _type(type)
{
    _colorType[LINEMATE] 	= glm::vec4(1, 0, 0, 0.2); // Red
    _colorType[DERAUMERE] 	= glm::vec4(0, 1, 0, 0.2); // Green
    _colorType[SIBUR] 		= glm::vec4(0, 0, 1, 0.2); // Blue
    _colorType[MENDIANE] 	= glm::vec4(1, 1, 0, 0.2); // Yellow
    _colorType[PHIRAS] 		= glm::vec4(1, 0, 1, 0.2); // Pink
    _colorType[THYSTAME] 	= glm::vec4(0, 1, 1, 0.2); // Cyan
    
    _model = new Model;
    _model->loadObj("res/models/gem/gem.obj", "res/models/gem/gem.png");
    
//    _position.x = ((cpu_cycle() % 6) / 10.0f) - 0.25f;
//    _position.y = 0.5f;
//    _position.z = ((cpu_cycle() % 6) / 10.0f) - 0.25f;
    
    _position.x = ((cpu_cycle() % 6));
    _position.y = 0.5f;
    _position.z = ((cpu_cycle() % 6));
    
    _model->translate(_position);
}

Gem::Gem(const Gem &gem, GemType type)
{
    _model = new Model(*gem._model);
    _type = type;
    _colorType = gem._colorType;
    
    //    _position.x = ((cpu_cycle() % 6) / 10.0f) - 0.25f;
    //    _position.y = 0.5f;
    //    _position.z = ((cpu_cycle() % 6) / 10.0f) - 0.25f;
    
    _position.x = ((cpu_cycle() % 6));
    _position.y = 0.5f;
    _position.z = ((cpu_cycle() % 6));
    
    _model->translate(_position);
}

Gem::~Gem()
{
    delete _model;
}

void	Gem::draw(Shader *shader)
{
    glm::vec3 tempPos = _model->getPos();
    
//    std::cout << "x: " << tempPos.x << " y: " << tempPos.y << " z: " << tempPos.z << std::endl;
    
//    shader->setUniform("light", glm::vec4(tempPos.x, tempPos.y + 0.5f, tempPos.z, 1.0f));
//    shader->setUniform("gColor", _colorType[_type]);
    _model->draw(shader);
}

void	Gem::destroyGeometry()
{
    _model->destroyGeometry();
}