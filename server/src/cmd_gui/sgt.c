/*
** sgt.c for sgt.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 28 16:43:44 2014 Nicolas Bridoux
** Last update Wed May 28 16:55:20 2014 Nicolas Bridoux
*/

#include "server.h"

void	sgt(t_server *serv, __attribute__((unused))t_selfd *fd,
	    __attribute__((unused))char **args)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "%zu", serv->game.time);
  send_response(fd, buff);
}
