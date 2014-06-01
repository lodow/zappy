/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Thu Apr 10 21:06:48 2014 Hugues
*/

#include "network.h"

/*
** Connect in a non blocking way, you should not use the socket until
** is_connected returned successfully.
*/

int	connect_nb(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
  int	ret;

  if (((ret = fcntl(sockfd, F_SETFL, O_NONBLOCK)) == -1)
      || (((ret = connect(sockfd, addr, addrlen)) == -1)
          && (errno != EINPROGRESS)))
    return (ret);
  if ((ret = (fcntl(sockfd, F_SETFL, ~O_NONBLOCK) == -1)))
    return (ret);
  return (0);
}

/*
** Check if the socket is connected return quickly
*/

int			is_connected(t_net *net)
{
  int			ret;
  socklen_t		len;
  fd_set		fdset;
  struct timeval	tv;

  errno = EFAULT;
  if (!net)
    return (-1);
  len = sizeof(int);
  tv.tv_sec = 0;
  tv.tv_usec = 20;
  FD_ZERO(&fdset);
  FD_SET(net->socket, &fdset);
  if ((ret = (select(net->socket + 1, NULL, &fdset, NULL, &tv)) <= 0))
    return (ret);
  if ((getsockopt(net->socket, SOL_SOCKET, SO_ERROR, (void*)(&ret),
                  &len) == -1) || (ret < 0) || getsockname(net->socket,
                      (struct sockaddr*)(&(net->addr)), &(net->addrlen)) == -1)
    {
      close_connection(net);
      if (ret < 0)
        errno = ret;
      return (-1);
    }
  return (1);
}
