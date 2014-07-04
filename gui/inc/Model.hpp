
#ifndef MODEL_HPP_
# define MODEL_HPP_

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
    
    void    loadObj(std::string const& path, bool texture);
    int     getLoadPercentage() const;
    
    void    draw(Shader *shader);
    
private:
    int         _load;
    
    Geometry    *_geometry;
    sf::Texture *_texture;
};

#endif
