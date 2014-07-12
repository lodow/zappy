#ifndef MAP_HPP_
# define MAP_HPP_

# include <list>
# include "IEntity.hpp"
# include "Ground.hpp"
# include "Player.hpp"

class Map
{
public:
  typedef std::list<IEntity *>::const_iterator const_iterator;
  typedef std::list<IEntity *>::iterator iterator;
  typedef std::list<Player *> Players;

public:
  Map();
  virtual ~Map();
  Map::const_iterator begin() const;
  Map::const_iterator end() const;
  Map::iterator begin();
  Map::iterator end();
  Map::Players::const_iterator playerBegin() const;
  Map::Players::const_iterator playerEnd() const;
  Map::Players::iterator playerBegin();
  Map::Players::iterator playerEnd();
  void removePlayer(Players::iterator player);
  void push_back(IEntity* val);
  void push_back(Player* val);
  size_t size() const;
  size_t playerSize() const;
  IEntity *back();
  Player *playerBack();
  const glm::vec2 &getSize() const;
  void setSize(const glm::vec2 &size);
  float getTime() const;
  void setTime(float time);

typedef std::list<IEntity *> Maps;

private:
  Maps _grounds;
  Players _players;
  glm::vec2 _size;
  float _time;
};

#endif /* MAP_HPP_ */
