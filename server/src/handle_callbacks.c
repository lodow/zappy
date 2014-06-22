/*
** handle_client.c for handle_client.c in /home/bridou_n/projets/zappy/server
**
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Thu May 22 18:30:00 2014 Nicolas Bridoux
** Last update Sat May 31 19:38:30 2014 Nicolas Bridoux
*/

#include "server.h"

int		handle_client(t_selfd *fd, t_server *serv)
{
  char		*cmd;
  int		r;
  ssize_t		swr;

  if (ISREADABLE(fd))
    {
      if (((r = read_from_client(fd)) < 0 && errno != EINTR) || (r == 0))
        {
          log_connection(((t_client *)fd->data)->sock,
                         "Client disconnected from:");
          return (destroy_connection(serv, fd));
        }
    }
  if (ISWRITEABLE(fd) && (r = write_to_client(fd)) < 0 && errno != EINTR)
    return (destroy_connection(serv, fd));
  while ((cmd = get_command(fd)))
    handle_add_cmd(serv, fd, cmd);
  swr = ring_buffer_left_read(fd->wbuff);
  if (!swr && fd->to_close)
    return (destroy_connection(serv, fd));
  if (swr)
    CHECKWRITE(fd);
  CHECKREAD(fd);
  push_instruction(serv, fd);
  return (0);
}
