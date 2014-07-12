
# include "Rectangle.hpp"

Rectangle::Rectangle(int x, int y, int sizeX, int sizeY)
: _sizeX(sizeX), _sizeY(sizeY), _screenPosition(glm::vec2(x, y))
{
    _texture = NULL;
    _geometry = NULL;
}

Rectangle::~Rectangle()
{
    if (_texture != NULL)
        delete _texture;
    if (_geometry != NULL)
        delete _geometry;
}

void	Rectangle::loadTexture(const std::string &path, bool smooth)
{
    if (_texture != NULL)
        delete _texture;
    _texture = new sf::Texture;
    _texture->loadFromFile(path);
    _texture->setRepeated(smooth);
}

void	Rectangle::draw(Shader *shader)
{
    sf::Texture::bind(_texture);
    _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
}

void	Rectangle::build()
{
    if (_geometry != NULL)
        delete _geometry;
    _geometry = new Geometry;
    
    _geometry->pushVertex(glm::vec3(_screenPosition.x, _screenPosition.y, 0.0f)).pushUv(glm::vec2(0, 0));
    _geometry->pushVertex(glm::vec3(_screenPosition.x, _screenPosition.y + _sizeY, 0.0f)).pushUv(glm::vec2(0, 1));
    _geometry->pushVertex(glm::vec3(_screenPosition.x + _sizeX, _screenPosition.y, 0.0f)).pushUv(glm::vec2(1, 0));
    
    _geometry->pushVertex(glm::vec3(_screenPosition.x + _sizeX, _screenPosition.y + _sizeY, 0.0f)).pushUv(glm::vec2(1, 1));
    _geometry->pushVertex(glm::vec3(_screenPosition.x, _screenPosition.y + _sizeY, 0.0f)).pushUv(glm::vec2(0, 1));
    _geometry->pushVertex(glm::vec3(_screenPosition.x + _sizeX, _screenPosition.y, 0.0f)).pushUv(glm::vec2(1, 0));

    _geometry->build(GL_STATIC_DRAW);
}