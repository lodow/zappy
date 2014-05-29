/*
** ppo.c for ppo.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 28 16:11:15 2014 Nicolas Bridoux
** Last update Thu May 29 23:23:47 2014 Nicolas Bridoux
*/

#include "server.h"

void		ppo_event(t_server *serv, t_selfd *fd)
{
  char		buff[BUFF_SIZE];
  t_client	*client;

  client = (t_client *)fd->data;
  snprintf(buff, sizeof(buff), "ppo %zu %zu %zu %d",
	   fd->cli_num, client->x,
	   client->y, client->orientation);
  send_to_every_gui(serv, buff);
}

void		ppo(t_server *serv, t_selfd *fd, char **args)
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
	      snprintf(buff, sizeof(buff), "ppo %zu %zu %zu %d",
		       fd_cli->cli_num, client->x,
		       client->y, client->orientation);
	      return (send_response(fd, buff));
	    }
	}
      tmp = tmp->next;
    }
  send_response(fd, "sbp");
}
