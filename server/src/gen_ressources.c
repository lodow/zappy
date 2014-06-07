/*
** gen_food.c for gen_food.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Sat Jun  7 14:31:38 2014 Nicolas Bridoux
** Last update Sat Jun  7 16:12:55 2014 Nicolas Bridoux
*/

#include "server.h"

void		gen_single_food(t_server *serv, char *ressource)
{
  size_t	x;
  size_t	y;

  if (ressource && !strcmp(ressource, "nourriture"))
    {
      x = rand() % serv->game.height;
      y = rand() % serv->game.width;
      serv->map[y][x].food++;
      bct_event(serv, &serv->map[y][x], x, y);
    }
}

void		gen_food(t_server *serv)
{
  size_t	x;
  size_t	y;

  y = 0;
  while (y < serv->game.height)
    {
      x = 0;
      while (x < serv->game.width)
	{
	  serv->map[y][x].food += rand() % MAX_ITEM_MAP;
	  ++x;
	}
      ++y;
    }
  mct_event(serv);
}

void		gen_rocks(t_server *serv, t_map *need)
{
  int		i;
  size_t	x;
  size_t	y;
  size_t	nb_need;

  i = 0;
  while (++i < 7)
    {
      nb_need = *((size_t *)need + i);
      while (nb_need > 0)
	{
	  x = rand() % serv->game.width;
	  y = rand() % serv->game.height;
	  ++(*((size_t *)&(serv->map[y][x]) + i));
	  bct_event(serv, &serv->map[y][x], x, y);
	  --nb_need;
	}
    }
}
