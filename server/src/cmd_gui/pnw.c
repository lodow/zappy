/*
** pnw.c for pnw.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 29 22:49:13 2014 Nicolas Bridoux
** Last update Sat May 31 17:24:44 2014 Nicolas Bridoux
*/

#include "server.h"

void		pnw_init(t_server *serv, t_selfd *fd)
{
  t_list	*tmp;
  t_selfd	*fd_cli;
  t_client	*client;
  char		buff[BUFF_SIZE];

  tmp = serv->watch;
  while (tmp)
    {
      fd_cli = (t_selfd *)tmp->data;
      if (fd_cli->callback == (void *)&handle_client)
	{
	  client = (t_client *)fd_cli->data;
	  if (client->type_cli == IA)
	    {
	      snprintf(buff, sizeof(buff), "pnw %zu %zu %zu %d %d %s",
		       fd_cli->cli_num, client->x, client->y,
		       conv_orient(client->orientation), client->level,
		       client->teamname);
	      send_response(fd, buff);
	    }
	}
      tmp = tmp->next;
    }
}

void		pnw(t_server *serv, t_selfd *fd)
{
  char		buff[BUFF_SIZE];
  t_client	*client;

  client = (t_client *)fd->data;
  snprintf(buff, sizeof(buff), "pnw %zu %zu %zu %d %d %s", fd->cli_num,
	   client->x, client->y, conv_orient(client->orientation), client->level,
	   client->teamname);
  send_to_every_gui(serv, buff);
}
