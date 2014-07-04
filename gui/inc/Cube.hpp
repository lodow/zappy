#ifndef _CUBE_H_
# define _CUBE_H_

# include <iostream>
# include <SFML/Graphics.hpp>
# include "IEntity.hpp"
# include "Geometry.hpp"

class Cube: public IEntity
{
public:
    Cube();
    Cube(const Cube &);
    virtual ~Cube() {};
    
    void    build();
    void    draw(Shader *shader);
    bool    loadTexture(const std::string &path);

private:
    Cube   &operator=(const Cube& c);
    
    Geometry    *_geometry;
    sf::Texture *_texture;
};

#endif /* _CUBE_H_ */
