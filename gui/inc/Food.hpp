#ifndef FOOD_HPP_
#define FOOD_HPP_

# include "IEntity.hpp"
# include "Model.hpp"


class Food : public IEntity
{
public:
    Food();
    Food(const Food &food, const glm::vec2 &pos);
    virtual ~Food();
    virtual void draw(Shader *shader) const;
    virtual void update(const sf::Clock &clock);
    
    virtual void setRecourse(const std::list<int> &recourse);
    virtual void setPosition(const glm::vec2 &pos);
    
    virtual const std::list<int> &getRecourse() const;
    virtual const glm::vec2 &getPosition() const;
    
    virtual const glm::vec3	&getSphereCenter() const;
    virtual const float		getSphereRadius() const;
    
private:
    Model 			*_model;
    glm::vec2 		_pos;
    std::list<int> 	_recourse;
    
    glm::vec3 		_sphereCenter;
    float			_sphereRadius;
};

#endif /* FOOD_HPP_ */
