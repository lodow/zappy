/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Thu Dec 13 13:14:01 2012 Hugues
*/

#include "server.h"

void		log_new_connection(t_net *sock)
{
  t_net		*tmp;
  char		*ip;

  if ((tmp = peer(sock)))
    {
      if ((ip = get_ip_addr(tmp)))
        printf("Client connected from: %s:%d\n", ip, port_number(tmp));
      free(ip);
      close_connection(tmp);
    }
}

void		handle_newconnection(t_selfd *fd, t_server *serv)
{
  t_net		*bind_sock;
  t_net		*nsock;
  t_selfd	*tmpfd;

  bind_sock = (t_net*)fd->data;
  if (!(nsock = accept_connection(bind_sock->socket)))
    return ;
  if (!(tmpfd = create_fd(nsock->socket, NULL, NULL)))
    {
      close_connection(nsock);
      return ;
    }
  log_new_connection(nsock);
  add_to_list(&(serv->watch), tmpfd);
}
