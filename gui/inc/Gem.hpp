
#ifndef GEM_HPP_
# define GEM_HPP_

# define ALPHA 0.8f

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

class Gem : public IEntity
{
    
public:
    Gem(GemType type);
    Gem(const Gem &gem, GemType type, const glm::vec2 &position);
    ~Gem();
    
    void destroyGeometry();
    void draw(Shader *shader);
    void setRecourse(const std::list<int> &recourse);
    virtual const std::list<int> &getRecourse() const;
    void setPosition(const glm::vec2 &pos);
    const glm::vec2 &getPosition() const;
    const glm::vec4 &getColor();
    
    
private:
    Model *_model;
    GemType _type;
    std::map<GemType, glm::vec4> _colorType;
    glm::vec2 _position;
    std::list<int> _recourse;
};

#endif
