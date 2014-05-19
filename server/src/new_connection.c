/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon May 19 11:32:10 2014 Nicolas Bridoux
*/

#include "server.h"

void		handle_client(t_selfd *fd, t_server *serv)
{
  t_client	*client;
  char		*cmd;
  int		r;

  client = (t_client *)(fd->data);
  if (ISREADABLE(fd))
    {
      if ((r = read_from_client(fd)) < 0)
	{
	  // erreur appropriée
	}
      if (!r)
	{
	  log_connection(client->sock, "Client disconnected from:");
	  close_connection(client->sock);
	  rm_from_list(&(serv->watch), find_in_list(serv->watch, fd), &free);
	  return ;
	}
    }
  if (fd->len_w && ISWRITEABLE(fd) && (r = write_to_client(fd)) < 0)
    {
      // erreur appropriée
    }
  if (fd->len_r && (cmd = get_command(fd)))
    {
      handle_exec_cmd(fd, cmd);
      free(cmd);
    }
  if (fd->len_w)
    CHECKWRITE(fd);
  CHECKREAD(fd);
}

void		log_connection(t_net *sock, char *message)
{
  t_net		*tmp;
  char		*ip;

  if ((tmp = peer(sock)))
    {
      if ((ip = get_ip_addr(tmp)))
        server_log(WARNING, "%s %s:%d", message, ip, port_number(tmp));
      free(ip);
      close_connection(tmp);
    }
}

void			handle_newconnection(t_selfd *fd, t_server *serv)
{
  t_net			*bind_sock;
  t_net			*nsock;
  t_selfd		*tmpfd;
  t_client		*client;

  CHECKREAD(fd);
  bind_sock = (t_net*)fd->data;
  if (!(nsock = accept_connection(bind_sock->socket)))
    return ;
  if ((!(client = malloc(sizeof(t_client))))
      || !(tmpfd = create_fd(nsock->socket, client, &handle_client)))
    {
      free(client);
      close_connection(nsock);
      return ;
    }
  client->sock = nsock;
  client->type_cli = UNKNOWN;
  client->teamname = NULL;
  log_connection(nsock, "New connection from:");
  add_to_list(&(serv->watch), tmpfd);
}
