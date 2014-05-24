/*
** fill_square_voir.c for fill_square_voir.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 23 19:49:14 2014 Nicolas Bridoux
** Last update Fri May 23 22:05:13 2014 Nicolas Bridoux
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

char		*add_square_voir(t_server *serv, int x, int y, char *saw)
{
  int		i;
  size_t	k;

  if (saw)
    saw = concat(saw, ",");
  if (!saw && !(saw = strdup("{")))
    return (NULL);
  i = -1;
  while (g_off[++i])
    {
      k = 0;
      while (k < *((size_t *)&serv->map[y][x] + i))
	{
	  saw = concat(saw, " ");
	  saw = concat(saw, g_off[i]);
	  ++k;
	}
    }
  return (saw);
}
