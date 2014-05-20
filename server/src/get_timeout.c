/*
** get_min_timeout.c for get_min_timeout.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 11:21:31 2014 Nicolas Bridoux
** Last update Tue May 20 17:31:12 2014 Nicolas Bridoux
*/

#include "server.h"

/*
** get the minimum timestamp on the life and action timeout of each clients
** and put it in tv->tv_usec
*/

static void	get_min_timeout(t_list *fds, struct timeval *tv)
{
  t_list	*tmp;
  t_selfd	*fd;
  t_client	*client;

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
}

/*
** put the différence of minimum timestamp found and now in "tv"
** if the différence is negative, 0 seconds of timeout is set
** (that mean the execution time has been longer than the minimum timeout found)
** if no timeout are found, NO_ACTION is set
*/

static void		get_real_timeout(struct timeval *tv)
{
  struct timeval	now;

  gettimeofday(&now, NULL);
  if (tv->tv_usec != NO_ACTION)
    {
      now.tv_usec += USEC(now.tv_sec);
      tv->tv_usec -= now.tv_usec;
      if (tv->tv_usec > 0)
	{
	  tv->tv_sec = tv->tv_usec / 1000000;
	  tv->tv_usec %= 1000000;
	}
      else
	{
	  tv->tv_sec = 0;
	  tv->tv_usec = 0;
	}
    }
}

struct timeval		*get_timeout(t_list *fds)
{
  struct timeval	*tv;

  if (!(tv = malloc(sizeof(struct timeval))))
    return (NULL);
  tv->tv_sec = 0;
  tv->tv_usec = NO_ACTION;
  get_min_timeout(fds, tv);
  get_real_timeout(tv);
  // server_log(WARNING, "real_timeout : %ld:%ld", tv->tv_sec, tv->tv_usec);
  return (tv->tv_usec == NO_ACTION ? NULL : tv);
}
