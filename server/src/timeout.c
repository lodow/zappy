/*
** timeout.c for timeout.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Mon May 19 20:49:41 2014 Nicolas Bridoux
** Last update Tue May 20 00:27:59 2014 Nicolas Bridoux
*/

#include "server.h"

void			set_timeout(t_client *client, char type, suseconds_t time)
{
  struct timeval	t;

  gettimeofday(&t, NULL);
  server_log(WARNING, "time = %ld", time);
  if (type == LIFE)
    {
      server_log(WARNING, "setting life timeout (%ld:%ld)", t.tv_sec + time / 1000000,
		 t.tv_usec + time % 1000000);
      client->life = USEC(t.tv_sec + (time / 1000000)) + t.tv_usec + time % 1000000;
    }
  else
    {
      server_log(WARNING, "setting action timeout (%ld:%ld)", t.tv_sec + time / 1000000,
		 t.tv_usec + time % 1000000);
      client->action = USEC(t.tv_sec + (time / 1000000)) + t.tv_usec + time % 1000000;
    }
}

struct timeval		*get_min_timeout(t_list *fds)
{
  struct timeval	*tv;
  struct timeval	now;
  t_list		*tmp;
  t_selfd		*fd;
  t_client		*client;

  if (!(tv = malloc(sizeof(struct timeval))))
    return (NULL);
  tv->tv_sec = 0;
  tv->tv_usec = NO_ACTION;
  tmp = fds;
  while (tmp)
    {
      fd = (t_selfd *)tmp->data;
      if (fd->fd_type == FD_CLI)
	{
	  client = (t_client *)fd->data;
	  if (client->action != NO_ACTION)
	    {
	      if (tv->tv_usec == NO_ACTION || client->life < tv->tv_usec)
		tv->tv_usec = client->action;
	    }
	  if (client->life != NO_ACTION)
	    {
	      if (tv->tv_usec == NO_ACTION || client->life < tv->tv_usec)
		tv->tv_usec = client->life;
	    }
	}
      tmp = tmp->next;
    }
  gettimeofday(&now, NULL); // si le temps d'exec > temps attente, retourner NULL
  server_log(WARNING, "current timeout: (%ld) %ld:%ld", tv->tv_usec,
	     tv->tv_usec / 1000000, tv->tv_usec % 1000000);
  if (tv->tv_usec != NO_ACTION)
    {
      tv->tv_sec = tv->tv_usec / 1000000;
      tv->tv_usec %= 1000000;
    }
  return (tv->tv_usec == NO_ACTION ? NULL : tv);
}

void			handle_timeout(t_server *serv, t_selfd *fd)
{
  struct timeval	now;
  t_list		*cmd;
  t_client		*client;

  client = (t_client *)fd->data;
  gettimeofday(&now, NULL);
  if (client->cmds && client->action == NO_ACTION)
    {
      cmd = top(client->cmds);
      // si la cmd est valide : set_timeout(client, ACTION, temps de la cmd)
      // sinon "ko"
    }
  if (client->action != NO_ACTION && client->action <= USEC(now.tv_sec) + now.tv_usec)
    {
      cmd = dequeue(&(client->cmds));
      // executer la cmd
    }


  if (client->life == NO_ACTION)
    {
      set_timeout(client, LIFE, 126 * serv->game.time);
    }
  if (client->life <= USEC(now.tv_sec) + now.tv_usec)
    {
      if (client->inv.food)
	{
	  server_log(WARNING, "%d perd 1 de nourriture\n", fd->cli_num);
	  --client->inv.food;
	  set_timeout(client, LIFE, 126 * serv->game.time);
	}
      else
	{
	  send_response(fd, "mort");
	  fd->to_close = 1;
	}
    }
}
