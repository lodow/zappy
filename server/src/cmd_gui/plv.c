/*
** plv.c for plv.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 28 16:26:03 2014 Nicolas Bridoux
** Last update Fri May 30 00:29:45 2014 Nicolas Bridoux
*/

#include "server.h"

void		plv_event(t_server *serv, size_t x, size_t y)
{
  char		buff[BUFF_SIZE];
  t_list	*tmp;
  t_selfd	*fd_cli;
  t_client	*client;

  tmp = serv->watch;
  while (tmp)
    {
      fd_cli = (t_selfd *)tmp->data;
      if (fd_cli->callback == (void *)&handle_client)
	{
	  client = (t_client *)fd_cli->data;
	  if (client->type_cli == IA && client->x == x && client->y == y)
	    {
	      snprintf(buff, sizeof(buff), "plv %zu %d",
		       fd_cli->cli_num, client->level);
	      send_to_every_gui(serv, buff);
	    }
	}
      tmp = tmp->next;
    }
}

void		plv(t_server *serv, t_selfd *fd, char **args)
{
  char		buff[BUFF_SIZE];
  t_list	*tmp;
  t_selfd	*fd_cli;
  t_client	*client;

  tmp = serv->watch;
  while (tmp)
    {
      fd_cli = (t_selfd *)tmp->data;
      if (args[0] && fd_cli->callback == (void *)&handle_client &&
	  fd_cli->cli_num == (size_t)atoi(args[0]))
	{
	  client = (t_client *)fd_cli->data;
	  if (client->type_cli == IA)
	    {
	      snprintf(buff, sizeof(buff), "plv %zu %d",
		       fd_cli->cli_num, client->level);
	      return (send_response(fd, buff));
	    }
	}
      tmp = tmp->next;
    }
  send_response(fd, "sbp");
}
