/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Fri May 23 22:14:48 2014 Nicolas Bridoux
*/

#include "server.h"

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

static int	init_new_client(t_server *serv, t_selfd *fd, t_client *client)
{
  client->type_cli = UNKNOWN;
  client->teamname = NULL;
  client->cmds = NULL;
  client->x = 0;
  client->y = 0;
  client->level = 1;
  client->orientation = DOWN;
  client->flag = OK;
  client->tmpcmd = NULL;
  client->tmpcmdsize = 0;
  memset(&(client->inv), 0, sizeof(t_map));
  fd->cli_num = serv->game.cli_num++;
  add_to_list(&(serv->watch), fd);
  send_response(fd, "BIENVENUE");
  set_timeout(serv, fd, "timeout", USEC(INIT_TIMEOUT));
  handle_client(fd, serv);
  return (EXIT_SUCCESS);
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
  if (!(nsock = accept_connection(bind_sock)))
    return (EXIT_FAILURE);
  if ((!(client = malloc(sizeof(t_client))))
      || !(tmpfd = create_fd(nsock->socket, client, &handle_client)))
    {
      free(client);
      close_connection(nsock);
      return (EXIT_FAILURE);
    }
  client->sock = nsock;
  log_connection(nsock, "New connection from:");
  return (init_new_client(serv, tmpfd, client));
}
