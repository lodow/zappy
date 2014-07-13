
#ifndef _CUBE6FACE_H_
# define _CUBE6FACE_H_

# include <iostream>
# include <SFML/Graphics.hpp>
# include "Geometry.hpp"
# include "AObject.hpp"

class Cube6Face : public AObject
{
public:
    Cube6Face();
    Cube6Face(const Cube6Face& c);
    Cube6Face& operator=(const Cube6Face& c);
    virtual ~Cube6Face();
    
    void	build();
    bool	loadTexture(const std::string &path, bool smooth = false);
    void	draw(Shader *shader);
    void	destroy();
    
private:
    Geometry	*_geometry;
    sf::Texture	*_texture;
};

#endif /* _CUBE6FACE_H_ */
