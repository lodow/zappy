/*
** add_team_names.c for add_team_names.c in /home/bridou_n/projets/zappy/server/src
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 19:28:20 2014 Nicolas Bridoux
** Last update Fri May 30 19:30:06 2014 Nicolas Bridoux
*/

#include "server.h"

int		check_team_names(t_list *list, char *progname,
				 t_server *server)
{
  t_list	*tmp;
  t_list	*team_names;

  team_names = list;
  while (list)
    {
      tmp = team_names;
      if (!strcmp(((t_team *)list->data)->name, "GRAPHIC"))
	return (fprintf(stderr, "%s: \"GRAPHIC\" is "
			"not a valid team-name\n", progname));
      ((t_team *)list->data)->max_cli = server->game.max_cli;
      while (tmp)
	{
	  if (tmp != list && !strcmp(((t_team *)tmp->data)->name,
				     ((t_team *)list->data)->name))
	    return (fprintf(stderr,
			    "%s: each team-name must be unique\n", progname));
	  tmp = tmp->next;
	}
      list = list->next;
    }
  return (EXIT_SUCCESS);
}
