/*
** inventaire.c for inventaire.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 18:02:41 2014 Nicolas Bridoux
** Last update Thu May 22 18:51:40 2014 Nicolas Bridoux
*/

#include "server.h"

void		inventaire(__attribute__((unused))t_server *server,
		   t_selfd *fd, __attribute__((unused))char **args)
{
  t_client	*client;
  char		inv[BUFF_SIZE];

  client = (t_client *)fd->data;
  snprintf(inv, sizeof(inv), "{nourriture %zu,linemate %zu,deraumere %zu,"
	   "sibur %zu,mendiane %zu,phiras %zu,thystame %zu}",
	   client->inv.food, client->inv.linemate, client->inv.deraumere,
	   client->inv.sibur, client->inv.mendiane, client->inv.phiras,
	   client->inv.thystame);
  send_response(fd, inv);
}
