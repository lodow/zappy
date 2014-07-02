/*
 * Parser.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: linard_f
 */

#include "/home/linard_f/unix/zappy/gui/inc/Parser.hpp"

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
