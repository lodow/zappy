
#ifndef MAP_HPP_
# define MAP_HPP_

# include <list>
# include "IEntity.hpp"
# include "Ground.hpp"
# include "Player.hpp"
# include "Egg.hpp"

class Map
{
public:
  typedef std::list<Ground *>::const_iterator const_iterator;
  typedef std::list<Ground *>::iterator iterator;
  typedef std::list<Player *> Players;
  typedef std::list<Egg *> Eggs;

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
  Map::Eggs::const_iterator eggBegin() const;
  Map::Eggs::const_iterator eggEnd() const;
  Map::Eggs::iterator eggBegin();
  Map::Eggs::iterator eggEnd();
  Map::Players::iterator removePlayer(Players::iterator player);
  Map::Eggs::iterator removeEgg(Eggs::iterator egg);
  Map::iterator erase(Map::iterator entity);
  void push_back(Ground* val);
  void push_back(Player* val);
  void push_back(Egg* val);
  size_t size() const;
  size_t playerSize() const;
  size_t eggSize() const;
  IEntity *back();
  Player *playerBack();
  const glm::vec2 &getSize() const;
  void setSize(const glm::vec2 &size);
  float getTime() const;
  void setTime(float time);

typedef std::list<Ground *> Maps;

private:
  Maps _grounds;
  Players _players;
  Eggs _eggs;
  glm::vec2 _size;
  float _time;
};

#endif /* MAP_HPP_ */
