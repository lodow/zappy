/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Thu May 22 18:17:13 2014 Nicolas Bridoux
*/

#include "server.h"

static int	max_fd_plusone(t_list *fds)
{
  int		max;
  t_list	*tmp;
  t_selfd	*fd;

  max = -1;
  tmp = fds;
  while (tmp)
    {
      fd = (t_selfd*)tmp->data;
      max = fd->fd > max ? fd->fd : max;
      tmp = tmp->next;
    }
  return (max + 1);
}

static void	set_fdset(t_list *fds, fd_set *setr, fd_set *setw)
{
  t_list	*tmp;
  t_selfd	*fd;

  FD_ZERO(setr);
  FD_ZERO(setw);
  tmp = fds;
  while (tmp)
    {
      fd = (t_selfd*)tmp->data;
      if ((fd->checktype & FDREAD) == FDREAD)
        FD_SET(fd->fd, setr);
      if ((fd->checktype & FDWRITE) == FDWRITE)
        FD_SET(fd->fd, setw);
      tmp = tmp->next;
    }
}

t_selfd		*create_fd(int fd, void *data, int (*call)())
{
  t_selfd	*res;

  if ((res = malloc(1 * sizeof(t_selfd))) == NULL)
    return (NULL);
  res->fd = fd;
  res->etype = 0;
  res->checktype = FDREAD;
  res->data = data;
  res->callback = call;
  res->rb_r = NULL;
  res->len_r = 0;
  res->rb_w = NULL;
  res->len_w = 0;
  res->to_close = 0;
  return (res);
}

t_list	*select_fd_set(t_list *fds, fd_set *setr,
		       fd_set *setw, struct timeval *tv)
{
  set_fdset(fds, setr, setw);
  if ((select(max_fd_plusone(fds), setr, setw, NULL, tv) == -1))
    {
      if (errno != EINTR)
        perror("Select");
      free(tv);
      return (NULL);
    }
  free(tv);
  return (fds);
}

/*
** Return a list of t_selfd which changed state
*/

void		do_select(t_list *fds, void *serv)
{
  fd_set	setr;
  fd_set	setw;
  t_list	*tmp;
  t_list	*nexttmp;
  t_selfd	*fd;
  int		disconnected;

  nexttmp = NULL;
  if ((tmp = select_fd_set(fds, &setr, &setw, get_timeout((t_server *)serv))))
    {
      nexttmp = tmp ? tmp->next : NULL;
      exec_instruction((t_server *)serv);
      while (tmp || nexttmp)
        {
          fd = (t_selfd *)tmp->data;
	  disconnected = 0;
	  if (FD_ISSET(fd->fd, &setr) || FD_ISSET(fd->fd, &setw))
	    {
	      fd->etype = (FD_ISSET(fd->fd, &setr)) * FDREAD
		+ (FD_ISSET(fd->fd, &setw)) * FDWRITE;
	      fd->checktype = 0;
	      disconnected = fd->callback(fd, serv);
	    }
	  push_instruction((t_server *)serv, disconnected ? NULL : fd);
          tmp = nexttmp;
          nexttmp = tmp ? tmp->next : NULL;
        }
    }
}
