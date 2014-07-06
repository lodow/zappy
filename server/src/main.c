/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sun Jul  6 09:54:19 2014 Nicolas Bridoux
*/

#include "server.h"

t_server	g_serv;

void	sig_handler(int sig)
{
  if (sig == SIGQUIT || sig == SIGINT || sig == SIGTERM)
    g_serv.quit = 1;
}

void	handle_server(t_server *serv)
{
  t_tv	tv;

  while (!serv->quit)
    {
      do_select(serv->watch, (get_timeout(serv, &tv) ? &tv : NULL), serv);
      exec_instruction(serv);
    }
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
  raw_mode(ON);
  if (!parse_command_line(&g_serv, ac, av) && (ret = 1))
    {
      if (!handle_start(&g_serv))
        {
          server_setup_select(&g_serv);
          handle_server(&g_serv);
        }
    }
  free_ptr_tab((void**)g_serv.listener, (void (*)(void*))&close_connection);
  quit_server(&g_serv);
  if (ret)
    server_log(WARNING, "Shutting down.. Now");
  raw_mode(OFF);
  return (ret);
}
