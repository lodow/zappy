/*
** pie.c for pie.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:21:09 2014 Nicolas Bridoux
** Last update Fri May 30 00:26:36 2014 Nicolas Bridoux
*/

#include "server.h"

void		pie(t_server *serv, t_selfd *fd, char result)
{
  char		buff[BUFF_SIZE];
  t_client	*client;

  client = (t_client *)fd->data;
  snprintf(buff, sizeof(buff), "pie %zu %zu %d",
	   client->x, client->y, result == OK);
  send_to_every_gui(serv, buff);
  plv_event(serv, client->x, client->y);
}
