/*
** add.c for add.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri Jul  4 10:34:31 2014 Nicolas Bridoux
** Last update Sat Jul 12 20:17:29 2014 Nicolas Bridoux
*/

#include "server.h"

extern char	*g_off[8];

static void	add_res(t_server *serv, char **args, int nb)
{
  int		i;

  i = -1;
  while (g_off[++i])
    {
      if (!strcmp(args[0], g_off[i]))
	{
	  gen_ressource(serv, g_off[i], nb, 1);
	  printf("%s%d %ss successfully added to the map.\n%s",
		 GREEN, nb, args[0], WHITE);
	  return ;
	}
    }
  printf("%s%s : is not a valid ressource.\n%s", RED, args[0], WHITE);
}

void	add(t_server *serv, char **args)
{
  int	nb;

  if (!args[0] || !args[1])
    {
      printf("%susage : add __res_name__ __nb__.\n%s", RED, WHITE);
      return ;
    }
  if ((nb = atoi(args[1])) <= 0)
    {
      printf("%snumber of ressources must be positive.\n%s", RED, WHITE);
      return ;
    }
  add_res(serv, args, nb);
}
