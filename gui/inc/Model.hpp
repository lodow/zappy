
#ifndef MODEL_HPP_
# define MODEL_HPP_

# ifndef GLM_FORCE_RADIANS
#  define GLM_FORCE_RADIANS
# endif

# include <SFML/Graphics.hpp>
# include <vector>
# include <glm/glm.hpp>
# include <iostream>
# include <sstream>
# include <fstream>
# include "Geometry.hpp"
# include "IEntity.hpp"

class Model: public AObject
{
    
public:
    Model();
    Model(const Model &model);
    virtual ~Model();
    
    void    loadObj(std::string const& objPath, const std::string &texturePath);
    int     getLoadPercentage() const;
    
    void    draw(Shader *shader);
    
    void	destroyGeometry();
    
private:
    int         _load;
    
    Geometry    *_geometry;
    sf::Texture *_texture;
};

#endif
