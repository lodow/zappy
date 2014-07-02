#ifndef _CUBE_H_
# define _CUBE_H_

# include <iostream>
# include <SFML/Graphics.hpp>
# include "AObject.hpp"
# include "Geometry.hpp"

class Cube: public AObject
{
public:
    Cube();
    virtual ~Cube() {};
    
    void    draw(Shader *shader);
    bool    loadTexture(const std::string &path);

private:
    Cube(const Cube& c);
    Cube   &operator=(const Cube& c);
    
    Geometry    *_geometry;
    sf::Texture *_texture;
};

#endif /* _CUBE_H_ */
