#ifndef EGG_HPP_
# define EGG_HPP_

# include "IEntity.hpp"
# include "Model.hpp"

class Egg : public IEntity
{
public:
  Egg();
  Egg(const Egg &egg, const glm::vec2 &pos, size_t nb);
  virtual ~Egg();
  virtual void draw(Shader *shader) const;
  virtual void update(const sf::Clock &clock, float serverSpeed);
  virtual void setRecourse(const std::list<int> &recourse);
  virtual void setPosition(const glm::vec2 &pos);
  virtual const std::list<int> &getRecourse() const;
  virtual const glm::vec2 &getPosition() const;
  size_t getNb() const;
  void setNb(size_t nb);

private:
  glm::vec2 _pos;
  std::list<int> _recourse;
  Model *_model;
  size_t _nb;
};

#endif /* EGG_HPP_ */
