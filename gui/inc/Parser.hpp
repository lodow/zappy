#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <list>
# include <map>
# include <string>
# include <iostream>
# include <sstream>
# include "Ground.hpp"
# include "Map.hpp"

class Parser
{
private:
    typedef void (Parser::*parse)(const std::string &cmd);
    typedef std::map<std::string, parse> Parse;
    
public:
    Parser(Map *map, Cube *cube, Gem *gem);
    virtual ~Parser();
    void parseCmd(const std::string &cmd);
    void parseBct(const std::string &cmd);
    void parsePnw(const std::string &cmd);
    void parsePpo(const std::string &cmd);
    void parsePdi(const std::string &cmd);
    
private:
    int getNbFromString(const std::string &str) const;
    
private:
    Map     *_map;
    Cube    *_cube;
    Gem     *_gem;
    Parse   _parse;
};

#endif /* PARSER_HPP_ */
