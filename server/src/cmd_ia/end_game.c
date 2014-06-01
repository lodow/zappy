/*
** end_game.c for end_game.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Sat May 31 20:05:02 2014 Nicolas Bridoux
** Last update Sat May 31 20:24:20 2014 Nicolas Bridoux
*/

#include "server.h"

static int	get_nb_at_end(t_server *serv, char *teamname)
{
  t_list	*tmp;
  t_selfd	*fd_cli;
  t_client	*client;
  int		nb;

  nb = 0;
  tmp = serv->watch;
  while (tmp)
    {
      fd_cli = (t_selfd *)tmp->data;
      if (fd_cli->callback == (void *)&handle_client)
	{
	  client = (t_client *)fd_cli->data;
	  if (client->teamname && !strcmp(client->teamname, teamname) &&
	      client->level == 8)
	    ++nb;
	}
      tmp = tmp->next;
    }
  return (nb);
}

void		check_end_game(t_server *serv)
{
  t_list	*tmp;

  tmp = serv->game.teams;
  while (tmp)
    {
      if (get_nb_at_end(serv, ((t_team *)tmp->data)->name) >= 6)
	{
	  seg(serv, ((t_team *)tmp->data)->name);
	  server_log(WARNING, "End of game: \"%s\" win",
		     ((t_team *)tmp->data)->name);
	  serv->quit = 1;
	  break ;
	}
      tmp = tmp->next;
    }
}
