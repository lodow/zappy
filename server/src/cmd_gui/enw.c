/*
** enw.c for enw.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:35:39 2014 Nicolas Bridoux
** Last update Fri May 30 01:13:56 2014 Nicolas Bridoux
*/

#include "server.h"

void		enw_init(t_server *serv, t_selfd *fd)
{
  t_list	*tmp;
  t_egg		*egg;
  char		buff[BUFF_SIZE];

  tmp = serv->game.eggs;
  while (tmp)
    {
      egg = (t_egg *)tmp->data;
      snprintf(buff, sizeof(buff), "enw %zu %zu %zu %zu", egg->num_egg,
	       egg->father, egg->x, egg->y);
      send_response(fd, buff);
      tmp = tmp->next;
    }
}

void		enw(t_server *serv, size_t num_egg, t_selfd *fd)
{
  t_client	*client;
  char		buff[BUFF_SIZE];

  client = (t_client *)fd->data;
  snprintf(buff, sizeof(buff), "enw %zu %zu %zu %zu", num_egg,
	   fd->cli_num, client->x, client->y);
  send_to_every_gui(serv, buff);
}
