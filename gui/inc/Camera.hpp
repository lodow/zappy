#ifndef _CAMERA_HPP_
# define _CAMERA_HPP_

# ifndef GLM_FORCE_RADIANS
#  define GLM_FORCE_RADIANS
# endif

# include <map>
# include <SFML/Window.hpp>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include "Player.hpp"

class Camera
{
public:
    Camera(int sizeX, int sizeY);
    ~Camera();
    
    void    lookAt();
    void    translate(glm::vec3 vec);
    
    void	updateView();
    void	updateKeys();
    
    bool	isFollowing() const;
    void	follow(Player *player);
    
    void	setPointView(glm::vec3 vec);
    void	setPos(glm::vec3 pos);
    
    const   glm::mat4 &getTransformation() const;
    const   glm::mat4 &getProjection() const;
    const   glm::vec3 &getPosView() const;
    const   glm::vec3 &getPos() const;
    
private:
    glm::mat4	_transformation;
    glm::mat4	_projection;
    
    glm::vec3	_pos;
    glm::vec3	_pos_view;
    glm::vec3	_dir;
    
    Player		*_player;
    bool		_following;
    
    int			_prevMouseX;
    int			_prevMouseY;
    float		_distance;
    float		_sensivity;
    float		_angley;
    float		_anglez;
};

#endif /* _CAMERA_HPP_ */
