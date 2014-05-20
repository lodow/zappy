/*
** prend.c for prend.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 18:13:17 2014 Nicolas Bridoux
** Last update Tue May 20 18:31:20 2014 Nicolas Bridoux
*/

#include "server.h"
#include "cmd.h"

t_off	g_off[] =
  {
    {"nourriture", 0},
    {"linemate", 1},
    {"deraumere", 2},
    {"sibur", 3},
    {"mendiane", 4},
    {"phiras", 5},
    {"thystame", 6},
    {NULL, 0},
  };

void		prend(t_server *serv, t_selfd *fd, char **args)
{
  t_client	*client;
  t_map		m;
  size_t	*obj;
  int		i;

  client = (t_client *)fd->data;
  if (args[0])
    {
      i = -1;
      while (g_off[++i].name)
	{
	  if (!strcmp(args[0], g_off[i].name))
	    {
	      m = serv->map[client->y][client->x];
	      obj = (size_t *)&m + g_off[i].off;

	      if (*obj > 0)
		{
		  --(*obj);
		  obj = (size_t *)&client->inv + g_off[i].off;
		  ++(*obj);
		  send_response(fd, "ok");
		}
	      else
		{
		  send_response(fd, "ko");
		}
	    }
	}
    }
}
