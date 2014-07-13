#include "Map.hpp"

Map::Map()
{
    _resized = false;
}

Map::~Map()
{
    
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

Map::Eggs::const_iterator Map::eggBegin() const
{
    return _eggs.begin();
}

Map::Eggs::const_iterator Map::eggEnd() const
{
    return _eggs.end();
}

Map::Eggs::iterator Map::eggBegin()
{
    return _eggs.begin();
}

Map::Eggs::iterator Map::eggEnd()
{
    return _eggs.end();
}

Map::Players::iterator Map::removePlayer(Players::iterator player)
{
    delete *player;
    return _players.erase(player);
}

Map::Eggs::iterator Map::removeEgg(Eggs::iterator egg)
{
    delete *egg;
    return _eggs.erase(egg);
}

Map::iterator Map::erase(Map::iterator entity)
{
    delete *entity;
    return _grounds.erase(entity);
}

void Map::push_back(Ground* val)
{
    _grounds.push_back(val);
}

void Map::push_back(Player* val)
{
    _players.push_back(val);
}

void Map::push_back(Egg* val)
{
    _eggs.push_back(val);
}

size_t Map::size() const
{
    return _grounds.size();
}

size_t Map::playerSize() const
{
    return _players.size();
}

size_t Map::eggSize() const
{
    return _eggs.size();
}

IEntity *Map::back()
{
    return _grounds.back();
}

Player *Map::playerBack()
{
    return _players.back();
}

const glm::vec2 &Map::getSize() const
{
    return _size;
}

void Map::setSize(const glm::vec2 &size)
{
    _size = size;
    _resized = true;
}

float Map::getTime() const
{
    return _time;
}

void Map::setTime(float time)
{
    _time = time;
}

void Map::setResized(bool resized)
{
    _resized = resized;
}

bool Map::isResized() const
{
    return (_resized);
}

const std::list<std::string> &Map::getTeamList() const
{
  return _teamList;
}

void Map::pushTeamName(const std::string &teamName)
{
  _teamList.push_back(teamName);
}
