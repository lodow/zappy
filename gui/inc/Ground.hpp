
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
    virtual void draw(Shader *shader);
    virtual void setRecourse(const std::list<int> &recourse);
    virtual const std::list<int> &getRecourse() const;
    virtual void setPosition(const glm::vec2 &pos);
    virtual const glm::vec2 &getPosition() const;
    const GemList &getGemList() const;
    
private:
    Gem _gem;
    Food _food;
    std::list<int> _recourse;
    GemList _gemList;
    glm::vec2 _position;
};

#endif /* GROUND_HPP_ */
