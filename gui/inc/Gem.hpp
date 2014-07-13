
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
    
    void destroyModel();
    virtual void draw(Shader *shader) const;
    virtual void update(const sf::Clock &clock, float serverSpeed);
    
    void setRecourse(const std::list<int> &recourse);
    void setPosition(const glm::vec2 &pos);
    
    virtual const std::list<int> 	&getRecourse() const;
    
    virtual const glm::vec2 &getPosition() const;
    GemType	getType() const;
    const glm::vec4 &getColor();
    
private:
    Model 	*_model;
    GemType _type;
    std::map<GemType, glm::vec4> _colorType;
    
    glm::vec2 	_position;
    std::list<int> _recourse;
};

#endif
