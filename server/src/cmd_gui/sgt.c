/*
** sgt.c for sgt.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 28 16:43:44 2014 Nicolas Bridoux
** Last update Fri Jul  4 10:52:31 2014 Nicolas Bridoux
*/

#include "server.h"

void	sgt(t_server *serv, t_selfd *fd,
	    __attribute__((unused))char **args)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "sgt %zu", serv->game.time);
  send_response(fd, buff);
}
