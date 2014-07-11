#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "IEntity.hpp"
# include "Model.hpp"

class Player : public IEntity
{
  enum Status {
    ALIVE,
    DYING,
    DEAD,
    SUMMONING
  };

public:
  Player();
  Player(const Player &player, const glm::vec2 &position, size_t nb, int lvl);
  virtual ~Player();
  void update(const sf::Clock &clock);
  virtual void draw(Shader *shader);
  virtual void setRecourse(const std::list<int> &recourse);
  virtual const std::list<int> &getRecourse() const;
  virtual const glm::vec2 &getPosition() const;
  virtual void setPosition(const glm::vec2 &pos);
  bool moveTo(const glm::vec2 &pos);
  size_t getNb() const;
  void setOrientation(size_t orientation);

typedef std::list<glm::vec2> PosList;
typedef std::list<glm::vec3> Way;

private:
  Status _status;
  size_t _nb;
  glm::vec2 _position;
  Model *_clarkKent;
  std::list<int> _recourse;
  size_t _lvl;
  PosList _posList;
  Way _way;
  std::list<size_t> _orientation;
  size_t _i;
};

#endif /* PLAYER_HPP_ */
