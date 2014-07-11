
#ifndef IENTITY_HPP_
# define IENTITY_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <glm/glm.hpp>
# include <list>
# include "Shader.hpp"
# include "AObject.hpp"

class IEntity
{
public:
    virtual ~IEntity() {};
    
    virtual void draw(Shader *shader) = 0;
    virtual void setRecourse(const std::list<int> &recourse) = 0;
    virtual const glm::vec2 &getPosition() const = 0;
    virtual void setPosition(const glm::vec2 &pos) = 0;
    virtual const glm::vec3 &getSphereCenter() const = 0;
    virtual const float getSphereRadius() const = 0;
    virtual const glm::mat4 &getTransformation() const = 0;
};

#endif /* IENTITY_HPP_ */
