#ifndef _PLAN_H_
# define _PLAN_H_

# include <iostream>
# include <SFML/Graphics.hpp>
# include "AObject.hpp"
# include "Geometry.hpp"

class Pan : public AObject
{
public:
    Pan(const glm::vec2 &size = glm::vec2(1, 1));
    virtual ~Pan();
    
    void build();
    
    void draw(Shader *shader);
    
private:
    Pan(const Pan& c);
    Pan& operator=(const Pan& c);
    
    glm::vec2	_size;
    
    Geometry	*_geometry;
    sf::Texture	*_texture;
};

#endif /* _PLAN_H_ */
