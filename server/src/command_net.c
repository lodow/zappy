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

char			*full_line(t_selfd *fd, char *part, size_t size)
{
  t_client		*client;
  char			*tmp;

  client = (t_client*)fd->data;
  if (!client || size == 0)
    return (NULL);
  if (!part)
    {
      client->tmpcmdsize = 0;
      free(client->tmpcmd);
      client->tmpcmd = NULL;
      return (NULL);
    }
  if ((tmp = realloc(client->tmpcmd, client->tmpcmdsize + size)))
    {
      client->tmpcmd = tmp;
      memcpy(&(client->tmpcmd[client->tmpcmdsize]), part, size);
      client->tmpcmdsize += size;
    }
  return (client->tmpcmd);
}

char			*get_command(t_selfd *fd)
{
  char			*cmd;
  char			*ptr;
  struct timeval	tv;
  size_t			size;
  char			buff[512];

  size = read_buffer(fd->rbuff, buff, sizeof(buff));
  if (size && ((cmd = memchr(buff, EOT_CHAR, size))))
    {
      rollback_read_buffer(fd->rbuff, size - (cmd - buff + 1));
      buff[(cmd - buff)] = '\0';
      if (((t_client*)fd->data)->tmpcmd != NULL
          && (ptr = full_line(fd, buff, (cmd - buff) + 1)))
        ptr = strdup(ptr);
      else
        ptr = strdup(buff);
      full_line(fd, NULL, 0);
      gettimeofday(&tv, NULL);
      if (ptr)
        server_log(RECEIVING, "%ld:%ld\t\tReceived \"%s\" from %d",
                   tv.tv_sec, tv.tv_usec, ptr, fd->cli_num);
      return (ptr);
    }
  full_line(fd, buff, size);
  return (NULL);
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
          server_log(ERROR, "Ring buffer overflow when sending %s\n"
                     "Ring Buffer will be extend !", to_send);
          extend_ring_buffer(fd->wbuff, len + 2);
        }
      CHECKWRITE(fd);
      write_buffer(fd->wbuff, to_send, len);
      write_buffer(fd->wbuff, &c, 1);
    }
}
