/*
** expulse.c for expulse.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Sat May 24 02:49:33 2014 Nicolas Bridoux
** Last update Thu May 29 23:41:01 2014 Nicolas Bridoux
*/

#include "server.h"

static int	get_deplacement(char orient_me, char orient_him)
{
  static int	cores[5][4] =
    {
      {5, 1, 7, 3},
      {1, 5, 3, 7},
      {3, 7, 5, 1},
      {7, 3, 1, 5}
    };
  return (cores[orient_me - 1][orient_him - 1]);
}

static void	expulse_client(t_server *serv, t_client *me,
			       t_selfd *fd)
{
  t_client	*him;
  char		buff[BUFF_SIZE];

  him = (t_client *)fd->data;
  if (me->orientation == UP)
    DOWN_Y(him->y);
  else if (me->orientation == DOWN)
    UP_Y(him->y);
  else if (me->orientation == LEFT)
    DOWN_X(him->x);
  else if (me->orientation == RIGHT)
    UP_X(him->x);
  ppo_event(serv, fd);
  if (me->x == him->x && me->y == him->y)
    return (send_response(fd, "deplacement: 0"));
  snprintf(buff, sizeof(buff), "deplacement: %d",
	   get_deplacement(me->orientation, him->orientation));
  send_response(fd, buff);
}

void		expulse(t_server *serv, t_selfd *fd,
		__attribute__((unused))char **args)
{
  t_list	*tmp;
  t_selfd	*fd_cli;
  t_client	*me;
  t_client	*him;
  char		ok;

  me = (t_client *)fd->data;
  tmp = serv->watch;
  ok = KO;
  while (tmp)
    {
      fd_cli = (t_selfd *)tmp->data;
      if (fd_cli->callback == (void *)&handle_client &&
	  (him = (t_client *)fd_cli->data) && fd_cli != fd &&
	  me->x == him->x && me->y == him->y && him->type_cli == IA)
	{
	  if (ok == KO)
	    pex(serv, fd);
	  expulse_client(serv, (t_client *)fd->data, fd_cli);
	  ok = OK;
	}
      tmp = tmp->next;
    }
  send_response(fd, (ok == OK) ? ("ok") : ("ko"));
}
