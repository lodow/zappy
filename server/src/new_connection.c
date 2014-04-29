/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Tue Apr 29 16:59:47 2014 Nicolas Bridoux
*/

#include "server.h"

void		handle_client(t_selfd *fd, t_server *serv)
{
  t_client	*client;
  int		r;

  client = (t_client *)(fd->data);
  if (ISREADABLE(fd))
    {
      // on add dans le ring buffer de lecture
      if ((r = read_from_client(fd)) > 0)
	{
	  // on voit si on peux executer une commande et décaler le ring buffer
	  check_command(fd);
	}
    }
  if (fd->len_w && ISWRITEABLE(fd))
    {
      // si on a des trucs dans le ring buffer d'écriture, on écrit
    }

  // on attend toujours une nouvelle commande ou la suite de celle en cours
  CHECKREAD(fd);

  // on monitore  uniquement si le ring buffer d'écriture n'est pas vide
  if (fd->len_w)
    CHECKWRITE(fd);
  if (r == 0) // quand la connexion est coupée
    {
      log_connection(client->sock, "Client disconnected from:");
      close_connection(client->sock);
      rm_from_list(&(serv->watch), find_in_list(serv->watch, fd), &free);
    }
}

void		log_connection(t_net *sock, char *message)
{
  t_net		*tmp;
  char		*ip;

  if ((tmp = peer(sock)))
    {
      if ((ip = get_ip_addr(tmp)))
        printf("%s %s:%d\n", message, ip, port_number(tmp));
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
  log_connection(nsock, "Client connected from:");
  add_to_list(&(serv->watch), tmpfd);
}
