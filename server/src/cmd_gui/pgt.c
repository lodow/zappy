/*
** pgt.c for pgt in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:44:48 2014 Nicolas Bridoux
** Last update Fri May 30 01:39:08 2014 Nicolas Bridoux
*/

#include "server.h"

void		pgt(t_server *serv, t_selfd *fd, int ressource_num)
{
  char		buff[BUFF_SIZE];
  t_client	*c;
  t_map		square;

  c = (t_client *)fd->data;
  snprintf(buff, sizeof(buff), "pgt %zu %d", fd->cli_num, ressource_num);
  send_to_every_gui(serv, buff);
  snprintf(buff, sizeof(buff), "pin %zu %zu %zu %zu %zu %zu %zu %zu %zu %zu",
	   fd->cli_num, c->x, c->y, c->inv.food,
	   c->inv.linemate, c->inv.deraumere, c->inv.sibur,
	   c->inv.mendiane, c->inv.phiras, c->inv.thystame);
  send_to_every_gui(serv, buff);
  square = serv->map[c->y][c->x];
  snprintf(buff, sizeof(buff), "bct %zu %zu %zu %zu %zu %zu %zu %zu %zu",
	   c->x, c->y, square.food, square.linemate, square.deraumere,
	   square.sibur, square.mendiane, square.phiras, square.thystame);
  send_to_every_gui(serv, buff);
}
