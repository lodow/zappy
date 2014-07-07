
#ifndef IENTITY_HPP_
# define IENTITY_HPP_

# include <glm/glm.hpp>
# include <list>
# include "Shader.hpp"
# include "AObject.hpp"

class IEntity: public AObject
{
public:
    virtual ~IEntity() {};
    
    virtual void draw(Shader *shader) = 0;
    virtual void setRecourse(const std::list<int> &recourse) = 0;
};

#endif /* IENTITY_HPP_ */
