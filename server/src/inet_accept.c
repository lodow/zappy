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

const char	*listening(int domain)
{
  if (domain == AF_INET)
    return ("0.0.0.0");
  else if (domain == AF_INET6)
    return ("::1");
  return (NULL);
}

t_net	*peer(t_net *net)
{
  t_net	*res;
  int	ret;

  if ((res = malloc(1 * sizeof(t_net))) == NULL)
    return (NULL);
  res->socket = -1;
  res->addrlen = sizeof(struct sockaddr_storage);
  ret = getpeername(net->socket, (struct sockaddr*)(&(res->addr)),
                    &(res->addrlen));
  if (ret)
    {
      perror("getpeername");
      free(res);
      return (NULL);
    }
  return (res);
}

int			port_number(t_net *net)
{
  in_port_t		port;
  struct sockaddr	*addr;

  addr = (struct sockaddr*)(&(net->addr));
  port = 0;
  if (addr->sa_family == AF_INET)
    port = (((struct sockaddr_in*)addr)->sin_port);
  else if (addr->sa_family == AF_INET6)
    port = (((struct sockaddr_in6*)addr)->sin6_port);
  return ((port == 0) ? 0 : ntohs(port));
}

t_net	*accept_connection(int sockfd)
{
  t_net	*res;

  if ((res = malloc(1 * sizeof(t_net))) == NULL)
    return (NULL);
  res->addrlen = sizeof(struct sockaddr_storage);
  res->socket = accept(sockfd, (struct sockaddr*)(&(res->addr)),
                       &(res->addrlen));
  if (res->socket == -1)
    {
      perror("accept");
      free(res);
      return (NULL);
    }
  return (res);
}

void	write_sock(const char *str, int socket, int strlen)
{
  int	len;

  len = 0;
  if (str != NULL)
    {
      if (strlen == -1)
        {
          while (str[len] != '\0')
            len++;
          strlen = len;
        }
      while ((len = write(socket, str, strlen)) != strlen)
        {
          if (len == -1)
            {
              perror("write");
              return ;
            }
          str = &(str[len]);
          strlen -= len;
        }
    }
}
