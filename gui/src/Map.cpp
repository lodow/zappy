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

Map::const_iterator Map::playerBegin() const
{
  return _players.begin();
}

Map::const_iterator Map::playerEnd() const
{
  return _players.end();
}

Map::iterator Map::playerBegin()
{
  return _players.begin();
}

Map::iterator Map::playerEnd()
{
  return _players.end();
}


void Map::push_back(IEntity* val)
{
  if (dynamic_cast<Ground *>(val))
    _grounds.push_back(val);
  else
    _players.push_back(val);
}

IEntity *Map::back()
{
  return _grounds.back();
}
