/*
** bct.c for bct.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 28 15:49:20 2014 Nicolas Bridoux
** Last update Fri May 30 01:37:26 2014 Nicolas Bridoux
*/

#include "server.h"

void		bct(t_server *serv, t_selfd *fd, char **args)
{
  char		buff[BUFF_SIZE];
  size_t	x;
  size_t	y;
  t_map		square;

  if (!args || !args[0] || !args[1])
    return (send_response(fd, "sbp"));
  x = atoi(args[0]);
  y = atoi(args[1]);
  if (x >= serv->game.width || y >= serv->game.height)
    return (send_response(fd, "suc"));
  square = serv->map[y][x];
  snprintf(buff, sizeof(buff), "bct %zu %zu %zu %zu %zu %zu %zu %zu %zu",
	   x, y, square.food, square.linemate, square.deraumere,
	   square.sibur, square.mendiane, square.phiras, square.thystame);
  send_response(fd, buff);
}
