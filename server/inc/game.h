/*
** game.h for game.h in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed Apr 30 17:49:57 2014 Nicolas Bridoux
** Last update Mon May 19 11:54:30 2014 Nicolas Bridoux
*/

#ifndef GAME_H_
# define GAME_H_

# include "liste.h"

# define MAX_ITEM_MAP	2

typedef struct	s_game
{
  size_t	width;
  size_t	height;
  size_t	time;
  size_t	max_cli;
  size_t	cli_num;
  t_list	*teams;
}		t_game;

typedef struct	s_map
{
  size_t	linemate;
  size_t	deraumere;
  size_t	sibur;
  size_t	mendiane;
  size_t	phiras;
  size_t	thystame;
}		t_map;

typedef struct	s_client
{
  t_net		*sock;
  char		type_cli;
  size_t	cli_num;
  char		*teamname;
  size_t	x;
  size_t	y;
  char		orientation;
}		t_client;

typedef struct	s_team
{
  char		*name;
  size_t	max_cli;
}		t_team;

#endif /* !GAME_H_ */
