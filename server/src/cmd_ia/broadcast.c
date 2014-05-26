/*
** broadcast.c for broadcast.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Mon May 26 23:15:06 2014 Nicolas Bridoux
** Last update Tue May 27 00:30:20 2014 Nicolas Bridoux
*/

#include "server.h"

static int	g_dir[8][4] =
  {
    {1, 5, 3, 7},
    {2, 6, 4, 8},
    {3, 7, 5, 1},
    {4, 8, 6, 2},
    {5, 1, 7, 3},
    {6, 2, 8, 4},
    {7, 3, 1, 5},
    {8, 4, 2, 6}
  };

static int	get_cores_direction(int square_location, char orientation)
{
  return (g_dir[square_location - 1][orientation - 1]);
}

static int	not_same_line_col(t_server *serv, t_client *me, t_client *him)
{
  int		dx;
  int		dy;

  dy = MIN(abs((int)me->x - (int)him->y),
	   (int)serv->game.height - abs((int)me->x - (int)him->y));
  dx = MIN(abs((int)me->x - (int)him->x),
	   (int)serv->game.width - abs((int)me->x - (int)him->x));
  if ((me->x + dy) % serv->game.height == him->y) // ca viens du haut
    {
      if ((me->x + dx) % serv->game.width == him->x)
	return (get_cores_direction(2, him->orientation)); // haut + gauche
      else
	return (get_cores_direction(8, him->orientation)); // haut + droite
    }
  // ca viens du bas
  if ((me->x + dx) % serv->game.width == him->x)
    return (get_cores_direction(4, him->orientation)); // bas + gauche
  else
    return (get_cores_direction(6, him->orientation)); // bas + droite
}

static int	get_direction(t_server *serv, t_client *me, t_client *him)
{
  int		dx;
  int		dy;

  dy = MIN(abs((int)me->x - (int)him->y),
	   (int)serv->game.height - abs((int)me->x - (int)him->y));
  dx = MIN(abs((int)me->x - (int)him->x),
	   (int)serv->game.width - abs((int)me->x - (int)him->x));
  server_log(WARNING, "dx = %d, dy = %d, tot = %d\n", dx, dy, dx + dy);
  if (!dx && !dy)
    return (0);
  if (!dx)
    {
      if ((me->x + dy) % serv->game.height == him->y)
	return (get_cores_direction(1, him->orientation)); // case du haut de B
      else
	return (get_cores_direction(5, him->orientation)); // case du bas de B
    }
  if (!dy)
    {
      if ((me->x + dx) % serv->game.width == him->x)
	return (get_cores_direction(3, him->orientation)); // case de gauche de B
      else
	return (get_cores_direction(7, him->orientation)); // case de droite de B
    }
  return (not_same_line_col(serv, me, him));
}

static void	send_broadcast(t_server *serv, t_client *me,
			       t_selfd *fd_cli, char *msg)
{
  t_client	*him;
  char		buff[BUFF_SIZE];

  him = (t_client *)fd_cli->data;
  snprintf(buff, sizeof(buff), "message %d,", get_direction(serv, me, him));
  msg = concat(strdup(buff), msg);
  send_response(fd_cli, msg);
}

void		broadcast(t_server *serv, t_selfd *fd, char **args)
{
  char		*msg;
  t_list	*tmp;
  t_selfd	*fd_cli;

  if (!(msg = strchr(*args, ' ')))
    return ;
  msg = strdup(++msg);
  tmp = serv->watch;
  while (tmp)
    {
      fd_cli = (t_selfd *)tmp->data;
      if (fd_cli != fd && fd_cli->callback == (void *)&handle_client)
	send_broadcast(serv, (t_client *)fd->data, fd_cli, msg);
      tmp = tmp->next;
    }
  free(msg);
  send_response(fd, "ok");
}
