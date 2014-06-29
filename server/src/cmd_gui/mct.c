/*
** mct.c for mct.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 28 16:00:44 2014 Nicolas Bridoux
** Last update Sat Jun  7 15:18:41 2014 Nicolas Bridoux
*/

#include "server.h"

static void	do_bct(t_map *map, size_t x, size_t y, t_selfd *fd)
{
  char		buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "bct %zu %zu %zu %zu %zu %zu %zu %zu %zu",
	   x, y, map->food, map->linemate, map->deraumere,
	   map->sibur, map->mendiane, map->phiras, map->thystame);
  send_response(fd, buff);
}

static void	do_bct_event(t_server *serv, t_map *map, size_t x, size_t y)
{
  char		buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "bct %zu %zu %zu %zu %zu %zu %zu %zu %zu",
	   x, y, map->food, map->linemate, map->deraumere,
	   map->sibur, map->mendiane, map->phiras, map->thystame);
  send_to_every_gui(serv, buff);
}

void		mct(t_server *serv, t_selfd *fd,
		    __attribute__((unused))char **args)
{
  size_t	x;
  size_t	y;

  x = 0;
  while (x < serv->game.height)
    {
      y = 0;
      while (y < serv->game.width)
	{
	  do_bct(&serv->map[y][x], x, y, fd);
	  ++y;
	}
      ++x;
    }
}

void		mct_event(t_server *serv)
{
  size_t	x;
  size_t	y;

  x = 0;
  while (x < serv->game.height)
    {
      y = 0;
      while (y < serv->game.width)
	{
	  do_bct_event(serv, &serv->map[y][x], x, y);
	  ++y;
	}
      ++x;
    }
}
