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

static t_server	g_serv;

void	sig_handler(int sig)
{
  if (sig == SIGQUIT || sig == SIGINT || sig == SIGTERM)
    {
      close_server_binds(&g_serv);
      g_serv.quit = 1;
    }
}

void	handle_server(t_server *serv)
{
  while (!serv->quit)
    do_select(serv->watch, serv);
}

int	main(UNSEDP int ac, UNSEDP char **av)
{
  int	ret;

  ret = 0;
  g_serv.listener = NULL;
  g_serv.watch = NULL;
  g_serv.quit = 0;
  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, &sig_handler);
  signal(SIGQUIT, &sig_handler);
  signal(SIGTERM, &sig_handler);
  if (listen_on_port(&g_serv, "4242", SOCK_STREAM))
    {
      close_server_binds(&g_serv);
      ret = 1;
    }
  else
    {
      serv_verbose(&g_serv);
      server_setup_select(&g_serv);
      handle_server(&g_serv);
    }
  quit_server(&g_serv);
  return (ret);
}
