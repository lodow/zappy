/*
** pin.c for pin.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 28 16:29:22 2014 Nicolas Bridoux
** Last update Wed May 28 16:41:29 2014 Nicolas Bridoux
*/

#include "server.h"

void		pin(t_server *serv, t_selfd *fd, char **args)
{
  char		buff[BUFF_SIZE];
  t_list	*tmp;
  t_selfd	*fd_cli;
  t_client	*c;

  tmp = serv->watch;
  while (tmp)
    {
      fd_cli = (t_selfd *)tmp->data;
      if (args[0] && fd_cli->callback == (void *)&handle_client &&
	  fd_cli->cli_num == (size_t)atoi(args[0]) &&
	  (c = (t_client *)fd_cli->data) && c->type_cli == IA)
	{
	  snprintf(buff, sizeof(buff),
		   "pin %zu %zu %zu %zu %zu %zu %zu %zu %zu %zu",
		   fd_cli->cli_num, c->x, c->y, c->inv.food,
		   c->inv.linemate, c->inv.deraumere, c->inv.sibur,
		   c->inv.mendiane, c->inv.phiras, c->inv.thystame);
	  return (send_response(fd, buff));
	}
      tmp = tmp->next;
    }
  send_response(fd, "sbp");
}
