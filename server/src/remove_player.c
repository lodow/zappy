/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sat Jul 12 20:14:16 2014 Nicolas Bridoux
*/

#include "server.h"

static void	regenerate_stones(t_server *serv, t_map *inv)
{
  gen_ressource(serv, "linemate", inv->linemate, 1);
  gen_ressource(serv, "deraumere", inv->deraumere, 1);
  gen_ressource(serv, "sibur", inv->sibur, 1);
  gen_ressource(serv, "mendiane", inv->mendiane, 1);
  gen_ressource(serv, "phiras", inv->phiras, 1);
  gen_ressource(serv, "thystame", inv->thystame, 1);
}

int		destroy_connection(t_server *serv, t_selfd *fd)
{
  t_list	*tmp;
  t_client	*client;

  server_log(WARNING, "Deleting player %zu", fd->cli_num);
  client = (t_client *)fd->data;
  regenerate_stones(serv, &client->inv);
  if (client->type_cli == IA)
    pdi(serv, fd->cli_num);
  close_connection(client->sock);
  tmp = serv->game.teams;
  while (tmp)
    {
      if (client->teamname &&
          !strcmp(((t_team *)tmp->data)->name, client->teamname) &&
	  ((t_team *)tmp->data)->max_cli < serv->game.max_cli)
        ++((t_team *)tmp->data)->max_cli;
      tmp = tmp->next;
    }
  clean_client(serv, fd);
  return (1);
}
