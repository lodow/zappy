#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/OpenGL.hpp>
# include <list>
# include <iostream>
# include "IEntity.hpp"

typedef std::list<IEntity *> Map;

class Parser
{
public:
  Parser(Map *map);
  virtual ~Parser();
  void parseCmd(std::string &cmd);

private:
  Map *_map;
};

#endif /* PARSER_HPP_ */
