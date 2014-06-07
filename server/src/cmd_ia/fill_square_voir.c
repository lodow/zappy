/*
** fill_square_voir.c for fill_square_voir.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 23 19:49:14 2014 Nicolas Bridoux
** Last update Sat Jun  7 17:09:54 2014 Nicolas Bridoux
*/

#include "server.h"

extern char	*g_off[8];

char	*concat(char *begin, char *to_add)
{
  char	*ret;

  if (!begin || !to_add)
    return (NULL);
  if (!(ret = malloc(sizeof(char) * (strlen(begin) + strlen(to_add) + 1))))
    return (NULL);
  strcpy(ret, begin);
  strcat(ret, to_add);
  free(begin);
  return (ret);
}

static size_t	nb_eggs_at(t_server *serv, size_t x, size_t y)
{
  t_list	*tmp;
  t_egg		*egg;
  size_t	nb;

  nb = 0;
  tmp = serv->game.eggs;
  while (tmp)
    {
      egg = (t_egg *)tmp->data;
      if (egg && egg->x == x && egg->y == y)
	++nb;
      tmp = tmp->next;
    }
  return (nb);
}

char		*add_player_and_eggs(t_server *serv, int x, int y, char *saw)
{
  size_t	p;
  size_t	k;

  k = -1;
  p = nb_players_at(serv, x, y, ALL);
  while (++k < p)
    saw = concat(saw, " joueur");
  k = -1;
  p = nb_eggs_at(serv, x, y);
  while (++k < p)
    saw = concat(saw, " oeuf");
  return (saw);
}

char		*add_square_voir(t_server *serv, int x, int y, char *saw)
{
  int		i;
  size_t	k;

  if (saw)
    saw = concat(saw, ",");
  if (!saw && !(saw = strdup("{")))
    return (NULL);
  i = -1;
  saw = add_player_and_eggs(serv, x, y, saw);
  while (g_off[++i])
    {
      k = -1;
      while (++k < *((size_t *)&serv->map[y][x] + i))
	{
	  saw = concat(saw, " ");
	  saw = concat(saw, g_off[i]);
	}
    }
  return (saw);
}
