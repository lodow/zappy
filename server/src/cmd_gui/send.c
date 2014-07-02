/*
** send.c for send.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 29 22:55:25 2014 Nicolas Bridoux
** Last update Thu May 29 23:00:12 2014 Nicolas Bridoux
*/

#include "server.h"

void		send_to_every_gui(t_server *serv, char *msg)
{
  t_list	*tmp;
  t_selfd	*fd_cli;
  t_client	*gui_cli;

  tmp = serv->watch;
  while (tmp)
    {
      fd_cli = (t_selfd *)tmp->data;
      if (fd_cli->callback == (void *)&handle_client)
	{
	  gui_cli = (t_client *)fd_cli->data;
	  if (gui_cli->type_cli == GUI)
	    send_response(fd_cli, msg);
	}
      tmp = tmp->next;
    }
}
