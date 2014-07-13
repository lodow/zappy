
#include "Parser.hpp"
#include "FormatException.hpp"

Parser::Parser(Map *map, Gem *gem, Player *player)
: _map(map), _gem(gem), _player(player), _food(new Food), _egg(new Egg)
{
    _parse["msz"] = &Parser::parseMsz;
    _parse["bct"] = &Parser::parseBct;
    _parse["pnw"] = &Parser::parsePnw;
    _parse["ppo"] = &Parser::parsePpo;
    _parse["pdi"] = &Parser::parsePdi;
    _parse["pin"] = &Parser::parsePin;
    _parse["sgt"] = &Parser::parseSgt;
    _parse["plv"] = &Parser::parsePlv;
    _parse["enw"] = &Parser::parseEnw;
    _parse["eht"] = &Parser::parseEht;
    _parse["pic"] = &Parser::parsePic;
    _parse["pie"] = &Parser::parsePie;
    _parse["pbc"] = &Parser::parsePbc;
    _parse["tna"] = &Parser::parseTna;
    _parse["seg"] = &Parser::parseSeg;
}

Parser::~Parser()
{
    
}

void Parser::parseCmd(const std::string &cmd)
{
    size_t pos = cmd.find_first_of(' ');
    
    try {
        if (pos == std::string::npos)
            throw FormatException();
        if (!cmd.size())
            return ;
        std::string tmp = cmd.substr(0, pos);
        if (_parse.find(tmp) != _parse.end()) {
            if ((pos = cmd.find_first_of(' ')) == std::string::npos)
                throw FormatException();
            (this->*_parse[tmp])(cmd.substr(pos + 1));
        }
    }
    catch (std::exception &e) {
        if (cmd != "BIENVENUE")
            std::cerr << e.what() << std::endl;
        return ;
    }
}

int Parser::getNbFromString(const std::string &str) const
{
    std::stringstream ss;
    size_t rank = 0;
    int nb = 0;
    
    rank = str.find_first_of(' ');
    if (!str.size())
        return 0;
    ss << str.substr(0, rank);
    ss >> nb;
    ss.clear();
    return nb;
}

void Parser::parseSgt(const std::string &cmd)
{
    float time = getNbFromString(cmd);
    
    if (!time)
        _map->setTime(10);
    else
        _map->setTime(time);
}

void Parser::parseMsz(const std::string &cmd)
{
    glm::vec2 pos;
    size_t rank = cmd.find_first_of(' ');
    
    if (rank == std::string::npos) {
        _map->setSize(glm::vec2(1, 1));
        throw FormatException();
    }
    pos.x = getNbFromString(cmd);
    pos.y = getNbFromString(cmd.substr(rank + 1));
    _map->setSize(pos);
    if (_map->size()) {
        for (Map::iterator it = _map->begin(); it != _map->end();) {
            it = _map->erase(it);
        }
        for (Map::Players::iterator it = _map->playerBegin(); it != _map->playerEnd();) {
            it = _map->removePlayer(it);
        }
        for (Map::Eggs::iterator it = _map->eggBegin(); it != _map->eggEnd();) {
            it = _map->removeEgg(it);
        }
    }
}

void Parser::parseBct(const std::string &cmd)
{
    glm::vec2 pos;
    std::string tmp = cmd;
    std::list<int> recourse;
    size_t rank = cmd.find_first_of(' ');
    
    if (rank == std::string::npos)
        throw FormatException();
    pos.x = getNbFromString(cmd);
    pos.y = getNbFromString(cmd.substr(rank + 1));
    tmp = cmd.substr(rank + 1);
    for (int i = 0; i != 7; ++i) {
        if ((rank = tmp.find_first_of(' ')) == std::string::npos)
            throw FormatException();
        tmp = tmp.substr(rank + 1);
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
    std::string team;
    size_t lvl;
    
    nb = getNbFromString(cmd);
    tmp = cmd.substr(cmd.find_first_of(' ') + 1);
    pos.x = getNbFromString(tmp);
    tmp = tmp.substr(tmp.find_first_of(' ') + 1);
    pos.y = getNbFromString(tmp);
    tmp = tmp.substr(tmp.find_first_of(' ') + 1);
    tmp = tmp.substr(tmp.find_first_of(' ') + 1);
    lvl = getNbFromString(tmp);
    team = tmp.substr(tmp.find_first_of(' ') + 1);
    _map->push_back(new Player(*_player, pos, nb, lvl, team));
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

void Parser::parsePlv(const std::string &cmd)
{
    size_t nb;
    size_t lvl;
    
    nb = getNbFromString(cmd);
    lvl = getNbFromString(cmd.substr(cmd.find_first_of(' ') + 1));
    for (Map::Players::const_iterator it = _map->playerBegin(), end = _map->playerEnd(); it != end; ++it) {
        if ((*it)->getNb() == nb)
            (*it)->setLvl(lvl);
    }
}

void Parser::parseEnw(const std::string &cmd)
{
    std::string tmp;
    size_t nb;
    glm::vec2 pos;
    
    nb = getNbFromString(cmd);
    tmp = cmd.substr(cmd.find_first_of(' ') + 1);
    tmp = tmp.substr(tmp.find_first_of(' ') + 1);
    pos.x = getNbFromString(tmp);
    tmp = tmp.substr(tmp.find_first_of(' ') + 1);
    pos.y = getNbFromString(tmp);
    _map->push_back(new Egg(*_egg, pos, nb));
}

void Parser::parseEht(const std::string &cmd)
{
    size_t nb = getNbFromString(cmd);
    
    for (Map::Eggs::iterator it = _map->eggBegin(), end = _map->eggEnd(); it != end; ++it)
        if ((*it)->getNb() == nb) {
            _map->removeEgg(it);
            return ;
        }
    
}

void Parser::parsePic(const std::string &cmd)
{
    glm::vec2 pos;
    
    pos.x = getNbFromString(cmd);
    pos.y = getNbFromString(cmd.substr(cmd.find_first_of(' ') + 1));
    for (Map::const_iterator it = _map->begin(), end = _map->end();  it != end; ++it) {
        if ((*it)->getPosition() == pos) {
            (*it)->setSummoning(true);
            return ;
        }
    }
}

void Parser::parsePie(const std::string &cmd)
{
    glm::vec2 pos;
    
    pos.x = getNbFromString(cmd);
    pos.y = getNbFromString(cmd.substr(cmd.find_first_of(' ') + 1));
    for (Map::const_iterator it = _map->begin(), end = _map->end();  it != end; ++it) {
        if ((*it)->getPosition() == pos) {
            (*it)->setSummoning(false);
            return ;
        }
    }
}

void Parser::parsePbc(const std::string &cmd)
{
    size_t nb;
    
    nb = getNbFromString(cmd);
    for (Map::Players::const_iterator it = _map->playerBegin(), end = _map->playerEnd(); it != end; ++it) {
        if ((*it)->getNb() == nb) {
            (*it)->setBroadcasting(true);
            return ;
        }
    }
}

void Parser::parseTna(const std::string &cmd)
{
  _map->pushTeamName(cmd);
}

void Parser::parseSeg(const std::string &cmd)
{
  // path of final picture : res/pictures/victory.jpg"
}
