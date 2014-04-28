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

static t_net	*g_server4;
static t_net	*g_server6;
static int	quit;

void	sig_handler(int sig)
{
  if (sig == SIGQUIT || sig == SIGINT || sig == SIGTERM)
    {
      if (g_server4)
        {
          if (g_server4->socket != -1)
            close(g_server4->socket);
          g_server4->socket = -1;
        }
      if (g_server6)
        {
          if (g_server6->socket != -1)
            close(g_server6->socket);
          g_server6->socket = -1;
        }
      quit = 1;
    }
}

void	serv_verbose()
{
  char	*ip[2];

  ip[0] = get_ip_addr(g_server4);
  ip[1] = get_ip_addr(g_server6);
  if (ip[0] && ip[1])
    printf("server waiting for connections on:\n %s:%d\n %s:%d\n",
           ip[0], port_number(g_server4), ip[1], port_number(g_server6));
  free(ip[0]);
  free(ip[1]);
}

void		do_server()
{
  t_server	serv;
  t_selfd	*fd[2];
  t_list	*tmp;

  serv_verbose();
  serv.watch  = NULL;
  fd[0] = create_fd(g_server4->socket, g_server4, &handle_newconnection);
  fd[1] = create_fd(g_server6->socket, g_server6, &handle_newconnection);
  add_to_list(&(serv.watch), fd[0]);
  add_to_list(&(serv.watch), fd[1]);
  if ((tmp = serv.watch))
    while (tmp->next)
      tmp = tmp->next;
  while (!quit)
    handle_server(&serv);
  rm_from_list(&(serv.watch), find_in_list(serv.watch, fd[0]), &free);
  rm_from_list(&(serv.watch), find_in_list(serv.watch, fd[1]), &free);
  rm_list(serv.watch, &close_client_connection);
  free_ptr_tab((void**)(serv.channels), &destroy_chan);
}

int	quit_server_err(int ret)
{
  close_connection(g_server4);
  close_connection(g_server6);
  return (ret);
}

int	main(UNSEDP int ac, char **av)
{
  g_server4 = NULL;
  g_server6 = NULL;
  quit = 0;
  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, &sig_handler);
  signal(SIGQUIT, &sig_handler);
  signal(SIGTERM, &sig_handler);
  if (!(g_server4 = create_connection(listening(AF_INET), av[1] ? av[1]
                                      : "6667", SOCK_STREAM, &bind))
      || !(g_server6 = create_connection(listening(AF_INET6), av[1] ? av[1]
                                         : "6667", SOCK_STREAM, &bind)))
    return (quit_server_err(1));
  if (listen(g_server4->socket, MAX_CLIENTS) == -1
      || listen(g_server6->socket, MAX_CLIENTS) == -1)
    {
      perror("listen");
      return (quit_server_err(1));
    }
  return (quit_server_err(0));
}
