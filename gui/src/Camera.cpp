
#include "Camera.hpp"

Camera::Camera()
: _pos(0.0, 0.0, 0.0), _pos_view(0.0, 0.0, 1.0), _dir(0.0, 1.0, 0.0)
{
    _projection = glm::perspective(60.0f, 1600.0f / 900.0f, 0.1f, 1000.0f);
    
    _translationKeyMap[sf::Keyboard::Up]    = glm::vec3(0, 0, -0.1);
    _translationKeyMap[sf::Keyboard::Down]  = glm::vec3(0, 0, 0.1);
    _translationKeyMap[sf::Keyboard::Left]  = glm::vec3(-0.1, 0, 0);
    _translationKeyMap[sf::Keyboard::Right] = glm::vec3(0.1, 0, 0);
}


Camera::~Camera()
{
    
}

void	Camera::lookAt()
{
    _transformation = glm::lookAt(_pos, _pos_view, _dir);
}

void	Camera::translate(glm::vec3 vec)
{
    _pos += vec;
    _pos_view += vec;
}

void	Camera::update(const sf::Keyboard::Key &key)
{
    translate(_translationKeyMap[key]);
}

const glm::mat4 &Camera::getTransformation() const
{
    return (_transformation);
}

const glm::mat4	&Camera::getProjection() const
{
    return (_projection);
}

void	Camera::setPointView(glm::vec3 vec)
{
    _pos_view = vec;
}

const glm::vec3	&Camera::getPosView() const
{
    return (_pos_view);
}

const glm::vec3	&Camera::getPos() const
{
    return (_pos);
}

void	Camera::setPos(glm::vec3 pos)
{
    _pos = pos;
}