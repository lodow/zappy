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

int		read_from_client(t_selfd *fd)
{
  char		buff[BUFSIZ];
  int		r;
  size_t	size;

  r = 0;
  size = ring_buffer_left_write(fd->rbuff);
  size = (size < sizeof(buff)) ? size : sizeof(buff);
  if (size && ((r = read(fd->fd, buff, size)) > 0))
    write_buffer(fd->rbuff, buff, r);
  return (r);
}

/*
** return the number of characters write and deleted from the circular buffer
*/

int		write_to_client(t_selfd *fd)
{
  size_t	size;
  char	buff[BUFSIZ];
  int		w;

  w = 0;
  size = read_buffer(fd->wbuff, buff, sizeof(buff));
  if (size)
    {
      if ((w = write(fd->fd, buff, size)) < 0)
        return (w);
    }
  rollback_read_buffer(fd->wbuff, size - w);
  return (w);
}

/*
** Get one line (\n) from ring buffer
*/

char			*get_command(t_selfd *fd)
{
  char			*cmd;
  char			*ptr;
  struct timeval	tv;
  size_t			size;
  char			buff[BUFSIZ];

  size = read_buffer(fd->rbuff, buff, sizeof(buff));
  if (size && ((cmd = memchr(buff, EOT_CHAR, sizeof(buff))))
      && (ptr = malloc(((cmd - buff) + 1) * sizeof(char))))
    {
      memcpy(ptr, buff, (cmd - buff));
      ptr[(cmd - buff)] = '\0';
      rollback_read_buffer(fd->rbuff, size - (cmd - buff + 1));
    }
  else
    return (NULL);
  gettimeofday(&tv, NULL);
  server_log(RECEIVING, "%ld:%ld\t\tReceived \"%s\" from %d",
             tv.tv_sec, tv.tv_usec, ptr, fd->cli_num);
  return (ptr);
}

/*
** add the content of to_send in the ring buffer (should be null terminated string)
*/

void			send_response(t_selfd *fd, char *to_send)
{
  size_t		len;
  struct timeval	tv;
  char			c;

  c = EOT_CHAR;
  if (!to_send || fd->to_close)
    return ;
  gettimeofday(&tv, NULL);
  server_log(SENDING, "%ld:%ld\t\tSending \"%s\" to %d",
             tv.tv_sec, tv.tv_usec, to_send, fd->cli_num);
  if ((len = strlen(to_send)))
    {
      if (ring_buffer_left_write(fd->wbuff) < len + 1)
        {
          server_log(ERROR, "Ring buffer under run when sending %s\n"
                     "Message will be truncated !", to_send);
        }
      CHECKWRITE(fd);
      write_buffer(fd->wbuff, to_send, len);
      write_buffer(fd->wbuff, &c, 1);
    }
}
