/*
** gauche.c for gauche.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 17:59:33 2014 Nicolas Bridoux
** Last update Thu May 29 23:23:26 2014 Nicolas Bridoux
*/

#include "server.h"

void		gauche(t_server *serv, t_selfd *fd,
		       __attribute__((unused))char **args)
{
  t_client	*client;

  client = (t_client *)fd->data;
  if (client->orientation == UP)
    client->orientation = LEFT;
  else if (client->orientation == DOWN)
    client->orientation = RIGHT;
  else if (client->orientation == LEFT)
    client->orientation = DOWN;
  else if (client->orientation == RIGHT)
    client->orientation = UP;
  send_response(fd, "ok");
  ppo_event(serv, fd);
}
