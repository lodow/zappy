/*
** prend.c for prend.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 18:13:17 2014 Nicolas Bridoux
** Last update Fri May 30 01:32:42 2014 Nicolas Bridoux
*/

#include "server.h"

char	*g_off[8] =
  {
    "nourriture",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    NULL
  };

void		prend(t_server *serv, t_selfd *fd, char **args)
{
  t_client	*client;
  int		i;

  client = (t_client *)fd->data;
  if (args[0])
    {
      i = -1;
      while (g_off[++i])
	if (!strcmp(args[0], g_off[i]))
	  {
	    if (*((size_t *)&(serv->map[client->y][client->x]) + i))
	      {
		--(*((size_t *)&(serv->map[client->y][client->x]) + i));
		++(*((size_t *)&client->inv + i));
		send_response(fd, "ok");
		pgt(serv, fd, i);
	      }
	    else
	      send_response(fd, "ko");
	    return ;
	  }
      send_response(fd, "ko");
    }
}
