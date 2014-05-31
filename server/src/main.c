/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sat May 31 19:39:33 2014 Nicolas Bridoux
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

int	main(int ac, char **av)
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
  if (parse_command_line(&g_serv, ac, av))
    {
      close_server_binds(&g_serv);
      ret = 1;
    }
  else
    {
      if (!handle_start(&g_serv))
	{
	  server_setup_select(&g_serv);
	  handle_server(&g_serv);
	}
    }
  quit_server(&g_serv);
  return (ret);
}
