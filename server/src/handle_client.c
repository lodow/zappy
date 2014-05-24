/*
** handle_client.c for handle_client.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 22 18:30:00 2014 Nicolas Bridoux
** Last update Thu May 22 18:32:17 2014 Nicolas Bridoux
*/

#include "server.h"

int		handle_client(t_selfd *fd, t_server *serv)
{
  t_client	*client;
  char		*cmd;
  int		r;

  client = (t_client *)(fd->data);
  if (ISREADABLE(fd))
    {
      if ((r = read_from_client(fd)) < 0 && errno != EINTR)
	return (close_connection(serv, fd));
      if (!r)
	{
	  log_connection(client->sock, "Client disconnected from:");
	  return (close_connection(serv, fd));
	}
    }
  if (fd->len_w && ISWRITEABLE(fd) &&
      (r = write_to_client(fd)) < 0 && errno != EINTR)
    return (close_connection(serv, fd));
  while (fd->len_r && (cmd = get_command(fd)))
    handle_add_cmd(serv, fd, cmd);
  if (!fd->len_w && fd->to_close)
    return (close_connection(serv, fd));
  if (fd->len_w)
    CHECKWRITE(fd);
  CHECKREAD(fd);
  return (0);
}
