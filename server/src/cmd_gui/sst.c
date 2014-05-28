/*
** sst.c for sst.h in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 28 16:52:09 2014 Nicolas Bridoux
** Last update Wed May 28 16:57:52 2014 Nicolas Bridoux
*/

#include "server.h"

void		sst(__attribute__((unused))t_server *serv, t_selfd *fd, char **args)
{
  char		buff[BUFF_SIZE];
  size_t	t;

  if (args[0])
    {
      if ((t = atoi(args[0])) <= 0)
	t = 1;
      serv->game.time = 1;
      snprintf(buff, sizeof(buff), "sgt %zu", serv->game.time);
      send_response(fd, buff);
    }
}
