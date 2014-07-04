
#include "Camera.hpp"

Camera::Camera()
: _pos(0.0, 0.0, 0.0), _pos_view(0.0, 0.0, 1.0), _dir(0.0, 1.0, 0.0)
{
    _projection = glm::perspective(70.0f, 500.0f / 500.0f, 1.0f, 1000.0f);
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

void	Camera::setPos(glm::vec3 pos)
{
    _pos = pos;
}

//void	Camera::setPlayer(bool player, t_gameinfo *gameInfo)
//{
//    float nbPlayer = (player == false) ? 1 : 2;
//    
//    _projection = glm::perspective(static_cast<float>(gameInfo->set->getVar(FOV)),
//                                   (static_cast<float>(gameInfo->set->getVar(W_WIDTH)) / nbPlayer)
//                                   / (static_cast<float>(gameInfo->set->getVar(W_HEIGHT))),
//                                   0.1f, 100.0f);
//}
