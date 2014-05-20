/*
** ring_buffers.c for ring_buffers.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue Apr 29 14:37:39 2014 Nicolas Bridoux
** Last update Tue May 20 10:32:06 2014 Nicolas Bridoux
*/

#include "server.h"

/*
** return the number of characters read and placed in the circular buffer
*/

int	read_from_client(t_selfd *fd)
{
  char	buff[READ_SIZE + 1];
  char	*new_rb;
  int	r;

  if ((r = read(fd->fd, buff, READ_SIZE)) > 0)
    {
      if ((new_rb = malloc(sizeof(char) * (fd->len_r + r))))
	{
	  if (fd->len_r)
	    memcpy(new_rb, fd->rb_r, fd->len_r);
	  memcpy(&new_rb[fd->len_r], buff, r);
	  free(fd->rb_r);
	  fd->rb_r = new_rb;
	  fd->len_r += r;
	}
    }
  return (r);
}

/*
** return the number of characters write and deleted from the circular buffer
*/

int	write_to_client(t_selfd *fd)
{
  int	r;
  char	*new_rb;

  // write 10 for testing
  if (fd->len_w && (r = write(fd->fd, fd->rb_w, fd->len_w > 10 ? 10 : fd->len_w)) > 0)
    {
      if ((new_rb = malloc(sizeof(char) * (fd->len_w - r + 1))))
	{
	  memcpy(new_rb, &fd->rb_w[r], fd->len_w - r);
	  new_rb[fd->len_w - r] = '\0';
	  free(fd->rb_w);
	  fd->rb_w = new_rb;
	  fd->len_w -= r;
	}
    }
  return (r);
}

/*
** return the first command from the ring buffer,
** NULL is returned if there is no complete command
*/

char		*get_command(t_selfd *fd)
{
  char		*ptr;
  char		*new_rb;
  char		*cmd;
  size_t	size_cmd;
  struct timeval tv;

  if (fd->len_r && (ptr = memchr(fd->rb_r, EOT_CHAR, fd->len_r)))
    {
      size_cmd = ptr - fd->rb_r;
      if ((cmd = malloc(sizeof(char) * (size_cmd + 1))))
	{
	  memcpy(cmd, fd->rb_r, size_cmd);
	  cmd[size_cmd] = '\0';
	}
      if ((new_rb = malloc(sizeof(char) * (fd->len_r - size_cmd))))
	{
	  memcpy(new_rb, &fd->rb_r[size_cmd + 1], fd->len_r - (size_cmd + 1));
	  free(fd->rb_r);
	  fd->rb_r = new_rb;
	  fd->len_r -= size_cmd + 1;
	}
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

void		send_response(t_selfd *fd, char *to_send)
{
  char		*new_rb;
  size_t	len;
  struct timeval tv;

  if (!to_send || fd->to_close)
    return ;
  gettimeofday(&tv, NULL);
  server_log(SENDING, "%ld:%ld\t\tSending \"%s\" to %d",
	     tv.tv_sec, tv.tv_usec, to_send, fd->cli_num);
  len = strlen(to_send);
  if ((new_rb = malloc(sizeof(char) * (fd->len_w + len + 2))))
    {
      if (fd->len_w)
	memcpy(new_rb, fd->rb_w, fd->len_w);
      memcpy(&new_rb[fd->len_w], to_send, len);
      new_rb[fd->len_w + len] = '\n';
      new_rb[fd->len_w + len + 1] = '\0';
      free(fd->rb_w);
      fd->rb_w = new_rb;
      fd->len_w += len + 1;
    }
}
