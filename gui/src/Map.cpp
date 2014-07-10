#include "Map.hpp"

Map::Map()
{
  // TODO Auto-generated constructor stub

}

Map::~Map()
{
  // TODO Auto-generated destructor stub
}

Map::const_iterator Map::begin() const
{
  return _grounds.begin();
}

Map::const_iterator Map::end() const
{
  return _grounds.end();
}

Map::iterator Map::begin()
{
  return _grounds.begin();
}

Map::iterator Map::end()
{
  return _grounds.end();
}

Map::Players::const_iterator Map::playerBegin() const
{
  return _players.begin();
}

Map::Players::const_iterator Map::playerEnd() const
{
  return _players.end();
}

Map::Players::iterator Map::playerBegin()
{
  return _players.begin();
}

Map::Players::iterator Map::playerEnd()
{
  return _players.end();
}


void Map::push_back(IEntity* val)
{
  _grounds.push_back(val);
}

void Map::push_back(Player* val)
{
  _players.push_back(val);
}


size_t Map::size() const
{
  return _grounds.size();
}

size_t Map::playerSize() const
{
  return _players.size();
}

IEntity *Map::back()
{
  return _grounds.back();
}

Player *Map::playerBack()
{
  return _players.back();
}
