
#include "Parser.hpp"

Parser::Parser(Map *map, Gem *gem, Player *player) : _map(map), _gem(gem), _player(player), _food(new Food)
{
  _parse["msz"] = &Parser::parseMsz;
  _parse["bct"] = &Parser::parseBct;
  _parse["pnw"] = &Parser::parsePnw;
  _parse["ppo"] = &Parser::parsePpo;
  _parse["pdi"] = &Parser::parsePdi;
  _parse["pin"] = &Parser::parsePin;
  _parse["sgt"] = &Parser::parseSgt;
}

Parser::~Parser()
{
    
}

void Parser::parseCmd(const std::string &cmd)
{
    std::string tmp = cmd.substr(0, cmd.find_first_of(' '));
    if (_parse.find(tmp) != _parse.end())
        (this->*_parse[tmp])(cmd.substr(cmd.find_first_of(' ') + 1));
}

int Parser::getNbFromString(const std::string &str) const
{
    std::stringstream ss;
    size_t rank = 0;
    int nb = 0;
    
    rank = str.find_first_of(' ');
    ss << str.substr(0, rank);
    ss >> nb;
    ss.clear();
    return nb;
}

void Parser::parseSgt(const std::string &cmd)
{
  float time = getNbFromString(cmd);

  _map->setTime(time);
}

void Parser::parseMsz(const std::string &cmd)
{
  glm::vec2 pos;

  pos.x = getNbFromString(cmd);
  pos.y = getNbFromString(cmd.substr(cmd.find_first_of(' ') + 1));
  _map->setSize(pos);
}

void Parser::parseBct(const std::string &cmd)
{
    glm::vec2 pos;
    std::string tmp = cmd;
    std::list<int> recourse;

    pos.x = getNbFromString(cmd);
    pos.y = getNbFromString(cmd.substr(cmd.find_first_of(' ') + 1));
    tmp = cmd.substr(cmd.find_first_of(' ') + 1);
    for (int i = 0; i != 7; ++i) {
	tmp = tmp.substr(tmp.find_first_of(' ') + 1);
	recourse.push_back(getNbFromString(tmp));
    }
    for (Map::const_iterator it = _map->begin(), end = _map->end();  it != end; ++it) {
        if ((*it)->getPosition().x == pos.x && (*it)->getPosition().y == pos.y) {
            (*it)->setRecourse(recourse);
            return ;
        }
    }
    _map->push_back(new Ground(pos, *_gem, *_food));
    _map->back()->setRecourse(recourse);

}

void Parser::parsePnw(const std::string &cmd)
{
  glm::vec2 pos;
  size_t nb;
  std::string tmp = cmd;
  size_t lvl;

  nb = getNbFromString(cmd);
  tmp = cmd.substr(cmd.find_first_of(' ') + 1);
  pos.x = getNbFromString(tmp);
  tmp = tmp.substr(tmp.find_first_of(' ') + 1);
  pos.y = getNbFromString(tmp);
  tmp = tmp.substr(tmp.find_first_of(' ') + 1);
  tmp = tmp.substr(tmp.find_first_of(' ') + 1);
  lvl = getNbFromString(tmp);
  _map->push_back(new Player(*_player, pos, nb, lvl));
}

void Parser::parsePpo(const std::string &cmd)
{
  glm::vec2 pos;
  size_t nb;
  std::string tmp = cmd;
  size_t orientation;

  nb = getNbFromString(cmd);
  tmp = cmd.substr(cmd.find_first_of(' ') + 1);
  pos.x = getNbFromString(tmp);
  tmp = tmp.substr(tmp.find_first_of(' ') + 1);
  pos.y = getNbFromString(tmp);
  tmp = tmp.substr(tmp.find_first_of(' ') + 1);
  orientation = getNbFromString(tmp) - 1;
  for (Map::Players::const_iterator it = _map->playerBegin(), end = _map->playerEnd(); it != end; ++it) {
      if ((*it)->getNb() == nb && (*it)->getStatus() != Player::DEAD) {
	  if ((*it)->moveTo(pos))
	    (*it)->setOrientation(orientation);
	  return ;
      }
  }
}

void Parser::parsePdi(const std::string &cmd)
{
  size_t nb;

  nb = getNbFromString(cmd);
  for (Map::Players::const_iterator it = _map->playerBegin(), end = _map->playerEnd(); it != end; ++it) {
      if ((*it)->getNb() == nb) {
	 (*it)->setStatus(Player::DYING);
	 return ;
      }
  }
}

void Parser::parsePin(const std::string &cmd)
{
  size_t nb;
  std::string tmp = cmd;
  std::list<int> recourse;

  nb = getNbFromString(cmd);
  tmp = cmd.substr(cmd.find_first_of(' ') + 1);
  tmp = tmp.substr(tmp.find_first_of(' ') + 1);
  for (int i = 0; i != 7; ++i) {
	tmp = tmp.substr(tmp.find_first_of(' ') + 1);
	recourse.push_back(getNbFromString(tmp));
  }
  for (Map::Players::const_iterator it = _map->playerBegin(), end = _map->playerEnd(); it != end; ++it) {
      if ((*it)->getNb() == nb) {
	  (*it)->setRecourse(recourse);
	  return ;
      }
  }

}
