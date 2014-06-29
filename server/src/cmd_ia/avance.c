/*
** avance.c for avance.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 17:42:57 2014 Nicolas Bridoux
** Last update Thu May 29 23:21:26 2014 Nicolas Bridoux
*/

#include "server.h"

void		avance(t_server *serv, t_selfd *fd,
		       __attribute__((unused))char **args)
{
  t_client	*client;

  client = (t_client *)fd->data;
  if (client->orientation == UP)
    client->y = (!client->y) ? (serv->game.height - 1) : (client->y - 1);
  if (client->orientation == DOWN)
    client->y = (client->y == serv->game.height - 1) ? (0) : (client->y + 1);
  if (client->orientation == LEFT)
    client->x = (!client->x) ? (serv->game.width - 1) : (client->x - 1);
  if (client->orientation == RIGHT)
    client->x = (client->x == serv->game.width - 1) ? (0) : (client->x + 1);
  send_response(fd, "ok");
  ppo_event(serv, fd);
}
