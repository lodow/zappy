#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/OpenGL.hpp>
# include <list>
# include <map>
# include <string>
# include <iostream>
# include <sstream>
# include "IEntity.hpp"
# include "Ground.hpp"

typedef std::list<IEntity *> Map;

class Parser
{
private:
  typedef void (Parser::*parse)(const std::string &cmd);
  typedef std::map<std::string, parse> Parse;

public:
  Parser(Map *map);
  virtual ~Parser();
  void parseCmd(std::string &cmd);
  void parseBct(const std::string &cmd);

private:
  int getNbFromString(const std::string &str) const;

private:
  Map *_map;
  Parse _parse;
};

#endif /* PARSER_HPP_ */
