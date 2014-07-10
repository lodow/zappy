
#ifndef _SKYBOX_H_
# define _SKYBOX_H_

# include "Cube6Face.hpp"

class SkyBox
{
public:
    explicit SkyBox();
    virtual ~SkyBox();
    
    void draw(Shader *shader, const glm::vec3 &position);
    
protected:
    Cube6Face	*_cube;
    sf::Texture _texture;
};

#endif /* _SKYBOX_H_ */
