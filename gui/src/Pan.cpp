
#include "Pan.hpp"

Pan::Pan(const glm::vec2 &size)
: _size(size)
{
    _geometry = NULL;
    _texture = NULL;
}

Pan::~Pan()
{
    if (_geometry != NULL)
        delete _geometry;
    if (_texture != NULL)
        delete _texture;
}

void	Pan::build()
{
    _geometry = new Geometry;
    _texture = new sf::Texture;
    
    _geometry->pushVertex(glm::vec3(0.5f, 0.5f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, 1.0));
    _geometry->pushVertex(glm::vec3(-0.5f, 0.5f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, 1.0));
    _geometry->pushVertex(glm::vec3(-0.5f, -0.5f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, 1.0));
    
    _geometry->pushVertex(glm::vec3(-0.5f, -0.5f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, 1.0));
    _geometry->pushVertex(glm::vec3(0.5f,  -0.5f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, 1.0));
    _geometry->pushVertex(glm::vec3(0.5f, 0.5f, 0.0f)).pushNormal(glm::vec3(0.0, 0.0, 1.0));
    
    _geometry->pushUv(glm::vec2(0.0f, 0.0f));
    _geometry->pushUv(glm::vec2(_size.y, 0.0f));
    _geometry->pushUv(glm::vec2(_size.y, _size.x));
    
    _geometry->pushUv(glm::vec2(_size.y, _size.x));
    _geometry->pushUv(glm::vec2(0.0f, _size.x));
    _geometry->pushUv(glm::vec2(0.0f, 0.0f));
    
    _geometry->build(GL_STATIC_DRAW);
    
    rotate(glm::vec3(1, 0, 0), -90);
    translate(glm::vec3((_size.x / 2) - 0.5f, 0.5f, (_size.y / 2) - 0.5f));
    scale(glm::vec3(_size.x + 1, _size.y + 1, 1));
    
    _texture->loadFromFile("res/textures/grass.png");
    _texture->setRepeated(true);
    _texture->setSmooth(true);
}

void	Pan::draw(Shader *shader)
{
    sf::Texture::bind(_texture);
    shader->setUniform("gColor", glm::vec4(1));
    _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
}