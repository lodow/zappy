/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sun Jul  6 09:54:18 2014 Nicolas Bridoux
*/

#include "server.h"

void	serv_verbose(t_server *serv)
{
  t_net	*tmp;
  char	*ip;
  int	i;

  i = 0;
  if (serv->listener)
    while (serv->listener[i])
      {
        tmp = serv->listener[i];
        ip = get_ip_addr(tmp);
        if (ip)
          printf("Listening on %s:%s%d%s\n", ip, GREEN,
                 port_number(tmp), WHITE);
        free(ip);
        ++i;
      }
}

int	listen_on_port(t_server *serv, char *port, int socktype)
{
  t_net	*bind4;
  t_net	*bind6;

  bind4 = NULL;
  bind6 = NULL;
  if (!port || !(bind4 = create_connection(listening(AF_INET), port,
                         socktype, &bind_reuse))
      || !(bind6 = create_connection(listening(AF_INET6), port,
                                     socktype, &bind_reuse))
      || (listen(bind4->socket, MAX_QUEUE) == -1)
      || (listen(bind6->socket, MAX_QUEUE) == -1))
    {
      if (bind4 && bind6)
        perror("Listen");
      close_connection(bind4);
      close_connection(bind6);
      return (1);
    }
  serv->listener = (t_net**)add_ptr_t_tab((void**)serv->listener,
                                          (void*)bind4);
  serv->listener = (t_net**)add_ptr_t_tab((void**)serv->listener,
                                          (void*)bind6);
  return (0);
}

void		server_setup_select(t_server *serv)
{
  t_selfd	*fd;
  t_net		*tmp;
  int		i;

  i = 0;
  if (serv->listener)
    while (serv->listener[i])
      {
        tmp = serv->listener[i];
        if ((fd = create_fd(tmp->socket, tmp, &handle_newconnection)))
          add_to_list(&(serv->watch), fd);
        i++;
      }
  if ((fd = create_fd(STDIN_FILENO, NULL, &handle_prompt)))
    add_to_list(&(serv->watch), fd);
}
