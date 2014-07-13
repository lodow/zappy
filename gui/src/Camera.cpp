
#include "Camera.hpp"

Camera::Camera(int sizeX, int sizeY)
: _pos(0.0, 0.0, 0.0), _pos_view(0.0, 0.0, 1.0), _dir(0.0, 1.0, 0.0)
{
    _projection = glm::perspective(glm::radians(50.0f), static_cast<float>(sizeX) / static_cast<float>(sizeY), 0.1f, 100.0f);
    _player = NULL;
    _following = false;
    _prevMouseX = 0;
    _prevMouseY = 0;
    _distance = 5;
    _sensivity = 0.4;
    _angley = 0;
    _anglez = 0;
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

void	Camera::updateView()
{
    if (_player != NULL)
        _pos_view = _player->getModelPos();
    else
        _following = false;
}

void	Camera::updateKeys()
{
    if (_player != NULL && _player->getStatus() == Player::DYING)
    {
        _following = false;
        _player = NULL;
        _pos_view = glm::vec3(0);
    }
    
    if (!_following)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            translate(glm::vec3(-0.1, 0, -0.1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            translate(glm::vec3(0.1, 0, 0.1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            translate(glm::vec3(-0.1, 0, 0.1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            translate(glm::vec3(0.1, 0, -0.1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            translate(glm::vec3(0.1, 0.1, 0.1));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            translate(glm::vec3(-0.1, -0.1, -0.1));
    }
}

bool	Camera::isFollowing() const
{
    return (_following);
}

void	Camera::follow(Player *player)
{
    if (player != NULL)
    {
        _player = player;
        _following = true;
    }
    else
    {
        _player = NULL;
        _following = false;
        _pos_view = glm::vec3(0);
    }
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