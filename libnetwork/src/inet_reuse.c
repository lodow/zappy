/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sat Jun  7 20:15:21 2014 Hugues
*/

#include "network.h"

/*
** Bind a socket to a port and reuse it.
*/

int	bind_reuse(int sockfd, const struct sockaddr *addr,
               socklen_t addrlen)
{
  int	yes;

  yes = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
      perror("setsockopt");
      return (-1);
    }
  return (bind(sockfd, addr, addrlen));
}
