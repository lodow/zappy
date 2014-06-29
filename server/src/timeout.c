/*
** timeout.c for timeout.c in /home/bridou_n/projets/zappy/server
**
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Mon May 19 20:49:41 2014 Nicolas Bridoux
** Last update Fri May 30 18:50:19 2014 Nicolas Bridoux
*/

#include "server.h"

void		display_serv_queue(t_server *serv)
{
  t_list	*tmp;
  t_instr	*new;

  tmp = serv->instr;
  while (tmp)
    {
      new = (t_instr *)tmp->data;
      if (new->fd)
	server_log(WARNING, " %d => \"%s\" => (%ld:%ld)",
		   new->fd->cli_num, new->cmd,
		   new->time / 1000000, new->time % 1000000);
      tmp = tmp->next;
    }
  server_log(WARNING, "");
}

void			set_timeout(t_server *serv, t_selfd *fd,
				    char *cmd, suseconds_t time)
{
  struct timeval	now;
  t_instr		*new;

  if (!cmd || !(new = malloc(sizeof(t_instr))))
    return ;
  gettimeofday(&now, NULL);
  now.tv_usec += USEC(now.tv_sec) + time;
  new->fd = fd;
  new->time = now.tv_usec;
  new->cmd = cmd;
  add_to_ordered_list(&(serv->instr), new, &sort_instr);
}

int		get_timeout(t_server *serv, struct timeval *tv)
{
  t_instr	*next;

  if (serv->instr && (next = (t_instr *)serv->instr->data))
    {
      gettimeofday(tv, NULL);
      tv->tv_usec += USEC(tv->tv_sec);
      tv->tv_usec = next->time - tv->tv_usec;
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
      return (1);
    }
  return (0);
}

