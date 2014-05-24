/*
** pose.c for pose.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 18:18:19 2014 Nicolas Bridoux
** Last update Fri May 23 22:51:39 2014 Nicolas Bridoux
*/

#include "server.h"

extern char	*g_off[8];

void		pose(t_server *serv, t_selfd *fd, char **args)
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
	    if (*((size_t *)&client->inv + i))
	      {
		--(*((size_t *)&client->inv + i));
		++(*((size_t *)&(serv->map[client->y][client->x]) + i));
		send_response(fd, "ok");
	      }
	    else
	      send_response(fd, "ko");
	    return ;
	  }
      send_response(fd, "ko");
    }
}
