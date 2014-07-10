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
  virtual void draw(Shader *shader);
  virtual void setRecourse(const std::list<int> &recourse);
  virtual void setPosition(const glm::vec2 &pos);
  virtual const glm::vec2 &getPosition() const;


private:
  Model *_model;
  glm::vec2 _pos;
};

#endif /* FOOD_HPP_ */
