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


/********************************/
/*** Utilization examples !!! ***/
/********************************/
void			dumb_client(t_selfd *fd, t_server *serv)
{
  t_dumb_client	*client;

//here you have the dumb client
  client = (t_dumb_client*)(fd->data);

  //check if you can read/write into it
  ISREADABLE(fd);
  ISWRITEABLE(fd);

  //this is just an example we should use ring buffers here !
  int tmp;
  char buff[4096];
  tmp = read(fd->fd, buff, sizeof(buff));
  write(fd->fd, buff, tmp);

  //to set if the fd should be monitored for read/write
  CHECKREAD(fd);
  CHECKWRITE(fd);


  if (tmp == 0) //Mean connection is closed
    {
    //  rm_from_list(&(serv->watch), find_in_list(serv->watch, fd),
    //               &close_client_connection);
    }
}

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

void			handle_newconnection(t_selfd *fd, t_server *serv)
{
  t_net			*bind_sock;
  t_net			*nsock;
  t_selfd		*tmpfd;
  t_dumb_client	*connection;

  bind_sock = (t_net*)fd->data;
  if (!(nsock = accept_connection(bind_sock->socket)))
    return ;
  if ((!(connection = malloc(1 * sizeof(t_dumb_client))))
      || !(tmpfd = create_fd(nsock->socket, connection, &dumb_client)))
    {
      free(connection);
      close_connection(nsock);
      return ;
    }
  log_new_connection(nsock);
  add_to_list(&(serv->watch), tmpfd);
}
