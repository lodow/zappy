/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef NETWORK_H_INCLUDED
# define NETWORK_H_INCLUDED

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define MAX_CLIENTS 50

typedef struct			s_net
{
  struct sockaddr_storage	addr;
  socklen_t			addrlen;
  int				socket;
  int				socktype;
}				t_net;

t_net		*create_connection(const char *host, const char *port,
                           int socktype, int	(*f)(int sockfd,
                               const struct sockaddr *addr,
                               socklen_t addrlen));
void		close_connection(t_net *net);
t_net	*accept_connection(int sockfd);
char		*get_ip_addr(t_net *net);
t_net	*peer(t_net *net);
const char	*listening(int domain);
int		port_number(t_net *net);

void	write_sock(const char *str, int socket, int strlen);

#endif /* !NETWORK_H_INCLUDED */
