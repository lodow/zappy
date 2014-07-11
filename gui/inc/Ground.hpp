
#ifndef GROUND_HPP_
# define GROUND_HPP_

# include "IEntity.hpp"
# include "Cube.hpp"
# include "Gem.hpp"

typedef std::list<Gem *> GemList;

class Ground : public IEntity
{
public:
    Ground(const glm::vec2 &pos, const Gem &gem);
    virtual ~Ground();
    
    void draw(Shader *shader);
    
    void setRecourse(const std::list<int> &recourse);
    void setPosition(const glm::vec2 &pos);

    const glm::mat4 &getTransformation() const;
    const glm::vec2 &getPosition() const;
    const GemList &getGemList() const;
    
    const glm::vec3 &getSphereCenter() const;
    const float 	getSphereRadius() const;
    
private:
    Gem 			_gem;
    std::list<int> 	_recourse;
    GemList 		_gemList;
    glm::vec2 		_position;

    glm::vec3 		_sphereCenter;
    float			_sphereRadius;
};

#endif /* GROUND_HPP_ */
