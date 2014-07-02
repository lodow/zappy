/*
** tna.c for tna.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 28 16:07:46 2014 Nicolas Bridoux
** Last update Wed May 28 16:11:05 2014 Nicolas Bridoux
*/

#include "server.h"

void		tna(t_server *serv, t_selfd *fd,
		    __attribute__((unused))char **args)
{
  t_list	*tmp;
  char		buff[BUFF_SIZE];

  tmp = serv->game.teams;
  while (tmp)
    {
      snprintf(buff, sizeof(buff), "tna %s", ((t_team *)tmp->data)->name);
      send_response(fd, buff);
      tmp = tmp->next;
    }
}
