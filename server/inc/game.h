/*
** game.h for game.h in /home/bridou_n/projets/zappy/server
**
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Wed Apr 30 17:49:57 2014 Nicolas Bridoux
** Last update Fri Jul  4 16:36:17 2014 Nicolas Bridoux
*/

#ifndef GAME_H_
# define GAME_H_

# include "liste.h"

# define MAX_ITEM_MAP	2
# define UP		1
# define DOWN		2
# define RIGHT		3
# define LEFT		4
# define INIT_TIMEOUT	10
# define OK		1
# define KO		2
# define TO_BORN	1
# define ALIVE		2
# define MOLDY_TIME	1200
# define ALL		-1
# define UP_Y(x)	(x = (x == serv->game.height - 1) ? (0) : (x + 1))
# define DOWN_Y(x)	(x = (!x) ? (serv->game.height - 1) : (x - 1))
# define UP_X(x)	(x = (x == serv->game.width - 1) ? (0) : (x + 1))
# define DOWN_X(x)	(x = (!x) ? (serv->game.width - 1) : (x - 1))
# define MIN(x, y)	((x < y) ? (x) : (y))

typedef struct	s_game
{
  size_t	width;
  size_t	height;
  suseconds_t	time;
  size_t	max_cli;
  size_t	cli_num;
  t_list	*eggs;
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
  char		flag;
  t_map		inv;
  char		*tmpcmd;
  size_t	tmpcmdsize;
  t_list	*cmds;
}		t_client;

typedef struct	s_team
{
  char		*name;
  size_t	max_cli;
}		t_team;

typedef struct	s_egg
{
  size_t	num_egg;
  size_t	father;
  size_t	x;
  size_t	y;
  char		*teamname;
  char		state;
}		t_egg;

#endif /* !GAME_H_ */
