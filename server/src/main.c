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

//void		do_server()
//{
//  t_server	serv;
//  t_selfd	*fd[2];
//  t_list	*tmp;
//
//  serv_verbose();
//  serv.watch  = NULL;
//  fd[0] = create_fd(g_server4->socket, g_server4, &handle_newconnection);
//  fd[1] = create_fd(g_server6->socket, g_server6, &handle_newconnection);
//  add_to_list(&(serv.watch), fd[0]);
//  add_to_list(&(serv.watch), fd[1]);
//  if ((tmp = serv.watch))
//    while (tmp->next)
//      tmp = tmp->next;
//  while (!quit)
//    handle_server(&serv);
//  rm_from_list(&(serv.watch), find_in_list(serv.watch, fd[0]), &free);
//  rm_from_list(&(serv.watch), find_in_list(serv.watch, fd[1]), &free);
//  rm_list(serv.watch, &close_client_connection);
//  free_ptr_tab((void**)(serv.channels), &destroy_chan);
//}


int		main(UNSEDP int ac, char **av)
{
  t_server	serv;

  serv.listener = NULL;
  serv.watch = NULL;
  serv.quit = 0;
  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, &sig_handler);
  signal(SIGQUIT, &sig_handler);
  signal(SIGTERM, &sig_handler);
  if (!listen_on_arr(&serv, "4242"))
    return (1);
  return (0);
}
