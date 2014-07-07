
#ifndef GEM_HPP_
# define GEM_HPP_

# include <map>
# include "Model.hpp"

enum GemType {
    LINEMATE = 0,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

class Gem: public IEntity
{

public:
    Gem(GemType type);
    Gem(const Gem &gem, GemType type);
    ~Gem();
    
    void draw(Shader *shader);
    virtual void setRecourse(const std::list<int> &recourse);
    
private:
    Model		*_model;
    GemType 	_type;
    glm::vec3	_position;
    std::map<GemType, glm::vec4> _colorType;
};

#endif
