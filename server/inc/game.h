/*
** game.h for game.h in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed Apr 30 17:49:57 2014 Nicolas Bridoux
** Last update Wed May 21 14:16:06 2014 Nicolas Bridoux
*/

#ifndef GAME_H_
# define GAME_H_

# include "liste.h"

# define MAX_ITEM_MAP	2
# define UP		0
# define DOWN		1
# define LEFT		2
# define RIGHT		3
# define NO_ACTION	-1
# define ACTION		1
# define LIFE		2
# define INIT_TIMEOUT	10

typedef struct	s_game
{
  size_t	width;
  size_t	height;
  suseconds_t	time;
  size_t	max_cli;
  size_t	cli_num;
  t_list	*teams;
}		t_game;

typedef struct	s_map
{
  size_t	food;
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
  char		*teamname;
  size_t	x;
  size_t	y;
  char		level;
  char		orientation;
  suseconds_t	action;
  suseconds_t	life;
  t_map		inv;
  t_list	*cmds;
}		t_client;

typedef struct	s_team
{
  char		*name;
  size_t	max_cli;
}		t_team;

#endif /* !GAME_H_ */
