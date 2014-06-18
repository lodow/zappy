/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Wed Jun 18 11:59:27 2014 Nicolas Bridoux
*/

#include "server.h"

int		destroy_connection(t_server *serv, t_selfd *fd)
{
  t_net		*net;
  t_list	*tmp;
  t_client	*client;

  server_log(WARNING, "Deleting player %zu", fd->cli_num);
  client = (t_client *)fd->data;
  if (client->type_cli == IA)
    pdi(serv, fd->cli_num);
  net = client->sock;
  close_connection(net);
  tmp = serv->game.teams;
  while (tmp)
    {
      if (client->teamname &&
          !strcmp(((t_team *)tmp->data)->name, client->teamname))
        ++((t_team *)tmp->data)->max_cli;
      tmp = tmp->next;
    }
  clean_client(serv, fd);
  return (1);
}
