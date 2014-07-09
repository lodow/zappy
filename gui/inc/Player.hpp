#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "IEntity.hpp"
# include "Model.hpp"

class Player : public IEntity
{
public:
  Player(const glm::vec2 &position);
  Player(const Player &player);
  virtual ~Player();
  virtual void draw(Shader *shader);
  virtual void setRecourse(const std::list<int> &recourse);
  virtual const glm::vec2 &getPosition() const;
  virtual void setPosition(const glm::vec2 &pos);

private:
  glm::vec2 _position;
  Model *_clarkKent;
  std::list<int> _recourse;
};

#endif /* PLAYER_HPP_ */
