/*
** ring_buffers.c for ring_buffers.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue Apr 29 14:37:39 2014 Nicolas Bridoux
** Last update Tue Apr 29 16:55:45 2014 Nicolas Bridoux
*/

#include "server.h"

/*
** return the number of characters read and placed in the circular buffer
*/

int	read_from_client(t_selfd *fd)
{
  char	buff[READ_SIZE + 1];
  char	*tmp;
  int	r;

  if ((r = read(fd->fd, buff, READ_SIZE)) > 0)
    {
      if ((tmp = malloc(sizeof(char) * (fd->len_r + r))))
	{
	  if (fd->rb_r)
	    memcpy(tmp, fd->rb_r, fd->len_r);
	  memcpy(&tmp[fd->len_r], buff, r);
	  free(fd->rb_r);
	  fd->rb_r = tmp;
	  fd->len_r += r;
	}
    }
  return (r);
}

void		check_command(t_selfd *fd)
{
  char		*ptr;
  char		*new_rb;
  char		*cmd;
  size_t	size_cmd;

  if (fd->rb_r && (ptr = memchr(fd->rb_r, EOT_CHAR, fd->len_r)))
    {
      size_cmd = ptr - fd->rb_r;
      if ((new_rb = malloc(sizeof(char) * (fd->len_r - size_cmd))))
	{
	  memcpy(new_rb, &fd->rb_r[size_cmd + 1], fd->len_r - (size_cmd + 1));
	  fd->len_r -= size_cmd + 1;
	}
      if ((cmd = malloc(sizeof(char) * (size_cmd + 1))))
	{
	  memcpy(cmd, fd->rb_r, size_cmd);
	  cmd[size_cmd] = '\0';

	  printf("cmd = {%s}, size_cmd = %zu\n", cmd, size_cmd);

	  if (fd->type_cli == UNKNOWN)
	    {
	      // on assigne le type si on peux avec la cmd
	    }
	  if (fd->type_cli == IA)
	    {
	      // ptr_func ia
	    }
	  if (fd->type_cli == GUI)
	    {
	      // ptr_func gui
	    }
	  free(cmd);
	}
      free(fd->rb_r);
      fd->rb_r = new_rb;
    }
}
