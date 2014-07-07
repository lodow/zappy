
#include "Parser.hpp"

Parser::Parser(Map *map, Cube *cube) : _map(map), _cube(cube)
{
    _parse["bct"] = &Parser::parseBct;
    
}

Parser::~Parser()
{
    
}

void Parser::parseCmd(std::string &cmd)
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
        if ((*it)->getPos().x == pos.x && (*it)->getPos().y == pos.y) {
            (*it)->setRecourse(recourse);
            return ;
        }
    }
    //_cube->setRecourse(recourse);
    _map->push_back(new Ground(pos, *_cube));
    _map->back()->setRecourse(recourse);

}
