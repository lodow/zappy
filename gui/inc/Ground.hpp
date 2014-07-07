
#ifndef GROUND_HPP_
# define GROUND_HPP_

# include "IEntity.hpp"
# include "Cube.hpp"
# include "Gem.hpp"

class Ground : public IEntity
{
public:
  Ground(const glm::vec2 &pos, const Cube &cube, const Gem &gem);
  virtual ~Ground();
  virtual void draw(Shader *shader);
  virtual void setRecourse(const std::list<int> &recourse);
  virtual const glm::vec2 &getPosition() const;
  virtual void setPosition(const glm::vec2 &pos);

typedef std::list<Gem *> GemList;

private:
  Cube _cube;
  Gem _gem;
  std::list<int> _recourse;
  GemList _gemList;
  glm::vec2 _position;
};

#endif /* GROUND_HPP_ */
