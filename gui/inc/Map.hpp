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

public:
  Map();
  virtual ~Map();
  Map::const_iterator begin() const;
  Map::const_iterator end() const;
  Map::iterator begin();
  Map::iterator end();
  Map::const_iterator playerBegin() const;
  Map::const_iterator playerEnd() const;
  Map::iterator playerBegin();
  Map::iterator playerEnd();
  void push_back(IEntity* val);
  IEntity *back();

typedef std::list<IEntity *> Maps;

private:
  Maps _grounds;
  Maps _players;

};

#endif /* MAP_HPP_ */
