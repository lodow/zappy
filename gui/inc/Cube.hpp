#ifndef _CUBE_H_
# define _CUBE_H_

# include <SFML/Graphics.hpp>
# include "Model.hpp"
# include "IEntity.hpp"
# include "Geometry.hpp"

class Cube: public AObject
{
public:
    Cube();
    Cube(const Cube &);
    virtual ~Cube();
    Cube   &operator=(const Cube& c);
    void    build();
    void    draw(Shader *shader);
    bool    loadTexture(const std::string &path);
    
    void    destroyGeometry();

private:
    Geometry    *_geometry;
    sf::Texture *_texture;
};

#endif /* _CUBE_H_ */
