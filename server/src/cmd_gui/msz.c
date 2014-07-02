/*
** msz.c for msz.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 28 15:44:12 2014 Nicolas Bridoux
** Last update Wed May 28 15:47:28 2014 Nicolas Bridoux
*/

#include "server.h"

void	msz(t_server *serv, t_selfd *fd,
	    __attribute__((unused))char **args)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "msz %zu %zu",
	   serv->game.width, serv->game.height);
  send_response(fd, buff);
}
