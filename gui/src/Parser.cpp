#include "Parser.hpp"

Parser::Parser(Map *map) : _map(map)
{

}

Parser::~Parser()
{

}

void Parser::parseCmd(std::string &cmd)
{
  std::cout << "cmd = " << cmd << std::endl;
}
