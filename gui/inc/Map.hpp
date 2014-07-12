#ifndef MAP_HPP_
# define MAP_HPP_

# include <list>
# include "IEntity.hpp"
# include "Ground.hpp"
# include "Player.hpp"

class Map
{
public:
  typedef std::list<Ground *>::const_iterator const_iterator;
  typedef std::list<Ground *>::iterator iterator;
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
  void push_back(Ground* val);
  void push_back(Player* val);
  size_t size() const;
  size_t playerSize() const;
  IEntity *back();
  Player *playerBack();
  const glm::vec2 &getSize() const;
  void setSize(const glm::vec2 &size);

typedef std::list<Ground *> Maps;

private:
  Maps _grounds;
  Players _players;
  glm::vec2 _size;

};

#endif /* MAP_HPP_ */
