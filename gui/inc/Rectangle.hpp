
#ifndef RECTANGLE_HPP_
# define RECTANGLE_HPP_

# include <SFML/Graphics.hpp>
# include "AObject.hpp"
# include "Geometry.hpp"
# include "Shader.hpp"

class Rectangle: public AObject
{
public:
    Rectangle(int x, int y, int sizeX, int sizeY);
    virtual ~Rectangle();
    
    void    build();
    void    draw(Shader *shader);
    void    loadTexture(const std::string &path, bool smooth = false);
    
private:
    int	_sizeX;
    int _sizeY;
    
    glm::vec2	_screenPosition;
    
    Geometry	*_geometry;
    
    sf::Texture	*_texture;
};

#endif