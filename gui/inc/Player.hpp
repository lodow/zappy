
#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "IEntity.hpp"
# include "Model.hpp"

# define COMPARE(a, b) std::abs(a - b) < FLT_EPSILON

class Player : public IEntity
{
public:
  enum Status {
    ALIVE = 0,
    DYING,
    DEAD,
    SUMMONING
  };

public:
    Player();
    Player(const Player &player, const glm::vec2 &position, size_t nb, int lvl);
    virtual ~Player();
    
    void	destroyModel();
    
    bool moveTo(const glm::vec2 &pos);
    
    virtual void draw(Shader *shader) const;
    virtual void update(const sf::Clock &clock, float serverSpeed);
    
    virtual void 	setPosition(const glm::vec2 &pos);
    virtual void 	setRecourse(const std::list<int> &recourse);
    void 			setOrientation(size_t orientation);
    
    size_t getNb() const;
    virtual const std::list<int> &getRecourse() const;
    virtual const glm::mat4 &getTransformation() const;
    virtual const glm::vec2 &getPosition() const;
    virtual const glm::vec3 &getSphereCenter() const;
    virtual const float		getSphereRadius() const;
    void setStatus(Status status);
    Status getStatus() const;

    
private:
    
    typedef std::list<glm::vec2> PosList;
    typedef std::list<glm::vec3> Way;
    
private:
    Status 			_status;
    size_t 			_nb;
    glm::vec2 		_position;
    glm::vec3		_sphereCenter;
    float			_sphereRadius;
    Model 			*_clarkKent;
    std::list<int> 	_recourse;
    size_t 			_lvl;
    PosList 		_posList;
    Way 			_way;
    std::list<size_t> _orientation;
//    size_t 			_i;
    float 			_distance;
    glm::vec2 		_previousPos;

//  Player();
//  Player(const Player &player, const glm::vec2 &position, size_t nb, int lvl);
//  virtual ~Player();
//  void update(const sf::Clock &clock, float speedOfServer);
//  virtual void draw(Shader *shader);
//  virtual void setRecourse(const std::list<int> &recourse);
//  virtual const std::list<int> &getRecourse() const;
//  virtual const glm::vec2 &getPosition() const;
//  virtual void setPosition(const glm::vec2 &pos);
//  bool moveTo(const glm::vec2 &pos);
//  size_t getNb() const;
//  void setOrientation(size_t orientation);
//  void setStatus(Status status);
//  Status getStatus() const;
//
//typedef std::list<glm::vec2> PosList;
//typedef std::list<glm::vec3> Way;
//
//private:
//  Status _status;
//  size_t _nb;
//  glm::vec2 _position;
//  Model *_clarkKent;
//  std::list<int> _recourse;
//  size_t _lvl;
//  PosList _posList;
//  Way _way;
//  std::list<size_t> _orientation;
//  float _distance;
//  glm::vec2 _previousPos;

};

#endif /* PLAYER_HPP_ */
