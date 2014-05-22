/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Thu May 22 17:59:53 2014 Nicolas Bridoux
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
      if ((r = read_from_client(fd)) < 0)
	{
	  // erreur appropriée
	}
      if (!r)
	{
	  log_connection(client->sock, "Client disconnected from:");
	  return (close_connection(serv, fd));
	}
    }
  if (fd->len_w && ISWRITEABLE(fd) && (r = write_to_client(fd)) < 0)
    {
      // erreur appropriée
    }
  while (fd->len_r && (cmd = get_command(fd)))
    handle_add_cmd(serv, fd, cmd);
  if (!fd->len_w && fd->to_close)
    return (close_connection(serv, fd));
  if (fd->len_w)
    CHECKWRITE(fd);
  CHECKREAD(fd);
  return (0);
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
      if (tmp && tmp->socket != -1 && close(tmp->socket) == -1)
	perror("close");
    }
}

int			handle_newconnection(t_selfd *fd, t_server *serv)
{
  t_net			*bind_sock;
  t_net			*nsock;
  t_selfd		*tmpfd;
  t_client		*client;

  CHECKREAD(fd);
  if (!ISREADABLE(fd))
    return (EXIT_FAILURE);
  bind_sock = (t_net*)fd->data;
  if (!(nsock = accept_connection(bind_sock->socket)))
    return (EXIT_FAILURE);
  if ((!(client = malloc(sizeof(t_client))))
      || !(tmpfd = create_fd(nsock->socket, client, &handle_client)))
    {
      free(client);
      if (nsock && nsock->socket != -1 && close(nsock->socket) == -1)
	perror("close");
      return (EXIT_FAILURE);
    }
  client->sock = nsock;
  client->type_cli = UNKNOWN;
  client->teamname = NULL;
  client->cmds = NULL;
  client->x = 0;
  client->y = 0;
  client->level = 1;
  client->orientation = DOWN;
  client->flag = OK;
  memset(&(client->inv), 0, sizeof(t_map));
  tmpfd->cli_num = serv->game.cli_num++;
  log_connection(nsock, "New connection from:");
  add_to_list(&(serv->watch), tmpfd);
  send_response(tmpfd, "BIENVENUE");
  set_timeout(serv, tmpfd, "timeout", USEC(INIT_TIMEOUT));
  handle_client(tmpfd, serv);
  return (EXIT_SUCCESS);
}
