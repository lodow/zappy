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

void	serv_verbose()
{
  char	*ip[2];

  ip[0] = get_ip_addr(g_server4);
  ip[1] = get_ip_addr(g_server6);
  if (ip[0] && ip[1])
    printf("Listening on:\n %s:%d\n %s:%d\n",
           ip[0], port_number(g_server4), ip[1], port_number(g_server6));
  free(ip[0]);
  free(ip[1]);
}

int	listen_on_port(t_server *serv, char *port)
{
  if (port)
    {
      if (!(server4 = create_connection(listening(AF_INET), port, SOCK_STREAM, &bind))
          || !(server6 = create_connection(listening(AF_INET6), port, SOCK_STREAM, &bind)))
        listen(g_server4->socket, MAX_CLIENTS);
      i++;
    }
  else
    return (1);
  return (0);
}
