/*
** voir.c for voir.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed May 21 15:06:45 2014 Nicolas Bridoux
** Last update Tue May 27 00:53:30 2014 Nicolas Bridoux
*/

#include "server.h"

static void	in_front(size_t *x, size_t *y,
			 char orientation, t_server *serv)
{
  if (orientation == UP)
    DOWN_Y(*y);
  if (orientation == DOWN)
    UP_Y(*y);
  if (orientation == LEFT)
    DOWN_X(*x);
  if (orientation == RIGHT)
    UP_X(*x);
}

static void	go_left(size_t *x, size_t *y,
			char orientation, t_server *serv)
{
  if (orientation == UP)
    DOWN_X(*x);
  if (orientation == DOWN)
    UP_X(*x);
  if (orientation == LEFT)
    UP_Y(*y);
  if (orientation == RIGHT)
    DOWN_Y(*y);
}

static void	look_line(size_t *x, size_t *y,
			  char orientation, t_server *serv)
{
  if (orientation == UP)
    UP_X(*x);
  if (orientation == DOWN)
    DOWN_X(*x);
  if (orientation == LEFT)
    DOWN_Y(*y);
  if (orientation == RIGHT)
    UP_Y(*y);
}

static char	*do_voir(t_server *serv, t_client *client,
			 char *saw, int depth)
{
  size_t	x;
  size_t	y;
  int		k;

  x = client->x;
  y = client->y;
  k = -1;
  while (++k < depth)
    in_front(&x, &y, client->orientation, serv);
  k = -1;
  while (++k < depth)
    go_left(&x, &y, client->orientation, serv);
  k = -1;
  while (++k < 2 * depth + 1 && (saw = add_square_voir(serv, x, y, saw)))
    look_line(&x, &y, client->orientation, serv);
  return (saw);
}

void		voir(t_server *serv, t_selfd *fd,
		     __attribute__((unused))char **args)
{
  t_client	*client;
  int		i;
  char		*saw;

  saw = NULL;
  client = (t_client *)fd->data;
  i = -1;
  // server_log(WARNING, "VOIR, client at (%d,%d) (orientaion = %d)",
  // 	     client->x, client->y, client->orientation);
  while (++i < client->level + 1)
    saw = do_voir(serv, client, saw, i);
  saw = concat(saw, "}");
  send_response(fd, saw);
  free(saw);
}
