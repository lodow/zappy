
#ifndef MODEL_HPP_
# define MODEL_HPP_

# include <SFML/Graphics.hpp>
# include <vector>
# include <glm/glm.hpp>
# include <iostream>
# include <sstream>
# include <fstream>
# include "Geometry.hpp"
# include "IEntity.hpp"

class Model: public IEntity
{
    
public:
    Model();
    virtual ~Model();
    
    void    loadObj(std::string const& objPath, const std::string &texturePath);
    int     getLoadPercentage() const;
    
    void    draw(Shader *shader);
    
private:
    int         _load;
    
    Geometry    *_geometry;
    sf::Texture *_texture;
};

#endif
