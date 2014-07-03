#ifndef _CAMERA_HPP_
# define _CAMERA_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();
    ~Camera();
    
    void    lookAt();
    void    translate(glm::vec3 vec);
    void	setPointView(glm::vec3 vec);
    void	setPos(glm::vec3 pos);
    
//    void	setPlayer(bool player, t_gameinfo *gameInfo);
    
    const   glm::mat4 &getTransformation() const;
    const   glm::mat4 &getProjection() const;
    const   glm::vec3 &getPosView() const;
    
private:
    glm::mat4	_transformation;
    glm::mat4	_projection;
    glm::vec3	_pos;
    glm::vec3	_pos_view;
    glm::vec3	_dir;
};

#endif /* _CAMERA_HPP_ */
