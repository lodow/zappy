
#ifndef GROUND_HPP_
# define GROUND_HPP_

# include "IEntity.hpp"
# include "Cube.hpp"
# include "Gem.hpp"
# include "Food.hpp"

typedef std::list<Gem *> GemList;

class Ground : public IEntity
{
public:
    Ground(const glm::vec2 &pos, const Gem &gem, const Food &food);
    virtual ~Ground();
    
    virtual void draw(Shader *shader) const;
    virtual void update(const sf::Clock &clock, float serverSpeed);
    
    virtual void setRecourse(const std::list<int> &recourse);
    virtual void setPosition(const glm::vec2 &pos);

    virtual const glm::vec2 &getPosition() const;
    
    virtual const std::list<int> &getRecourse() const;
    const GemList &getGemList() const;
    
    const glm::vec3 &getSphereCenter() const;
    float 	getSphereRadius() const;
    
    void		setSelected(bool selected);
    
private:
    Gem 			_gem;
    Food 			_food;
    std::list<int> 	_recourse;
    GemList 		_gemList;
    glm::vec2 		_position;
    bool			_selected;

    glm::vec3 		_sphereCenter;
    float			_sphereRadius;
};

#endif /* GROUND_HPP_ */
