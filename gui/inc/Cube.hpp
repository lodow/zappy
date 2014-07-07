#ifndef _CUBE_H_
# define _CUBE_H_

# include <SFML/Graphics.hpp>
# include <list>
# include "Model.hpp"
# include "IEntity.hpp"
# include "Geometry.hpp"

class Cube: public IEntity
{
public:
    Cube();
    Cube(const Cube &);
    virtual ~Cube();
    
    void    build();
    void    draw(Shader *shader);
    bool    loadTexture(const std::string &path);
    
    void    destroyGeometry();
    void    setRecourse(const std::list<int> &recourse);

private:
    Cube   &operator=(const Cube& c);
    
    Geometry    *_geometry;
    sf::Texture *_texture;
    std::list<int> _recourse;
};

#endif /* _CUBE_H_ */
