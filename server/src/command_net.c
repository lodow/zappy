/*
** ring_buffers.c for ring_buffers.c in /home/bridou_n/projets/zappy/server
**
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Apr 29 14:37:39 2014 Nicolas Bridoux
** Last update Fri May 30 18:26:38 2014 Nicolas Bridoux
*/

#include "server.h"

/*
** return the number of characters read and placed in the circular buffer
*/

int	read_from_client(t_selfd *fd)
{
  char	buff[BUFSIZ];
  int	r;

  if ((r = read(fd->fd, buff, BUFSIZ)) > 0)
    write_buffer(fd->rbuff, buff, r);
  return (r);
}

/*
** return the number of characters write and deleted from the circular buffer
*/

int		write_to_client(t_selfd *fd)
{
  ssize_t	size;
  char	buff[BUFSIZ];
  int		w;

  w = 0;
  size = read_buffer(fd->wbuff, buff, BUFSIZ);
  if (size)
    if ((w = write(fd->fd, buff, size)) < 0)
      return (w);
  rollback_read_buffer(fd->wbuff, size - w);
  return (w);
}

/*
** Get one line (\n) from ring buffer
*/

char			*get_command(t_selfd *fd)
{
  char			*ptr;
  char			*cmd;
  size_t		size_cmd;
  struct timeval	tv;

  if (fd->len_r && (ptr = memchr(fd->rb_r, EOT_CHAR, fd->len_r)))
    {
      size_cmd = ptr - fd->rb_r;
      cmd = has_a_complete_cmd(fd, size_cmd);
      gettimeofday(&tv, NULL);
      server_log(RECEIVING, "%ld:%ld\t\tReceived \"%s\" from %d",
                 tv.tv_sec, tv.tv_usec, cmd, fd->cli_num);
      return (cmd);
    }
  return (NULL);
}

/*
** add the content of to_send in the ring buffer (should be null terminated string)
*/

void			send_response(t_selfd *fd, char *to_send)
{
  size_t		len;
  struct timeval	tv;

  if (!to_send || fd->to_close)
    return ;
  gettimeofday(&tv, NULL);
  server_log(SENDING, "%ld:%ld\t\tSending \"%s\" to %d",
             tv.tv_sec, tv.tv_usec, to_send, fd->cli_num);
  if ((len = strlen(to_send)))
    CHECKWRITE(fd);
  write_buffer(fd->wbuff, to_send, len);
}
