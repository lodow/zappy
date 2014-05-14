/*
** parse_command_line.c for parse_command_line.c in /home/bridou_n/projets/zappy/server
**
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Wed Apr 30 17:20:06 2014 Nicolas Bridoux
** Last update Thu May  1 17:34:45 2014 Nicolas Bridoux
*/

#include "server.h"

static int	usage(char *av[])
{
  fprintf(stderr, "usage: %s [[[-p port] -p port] ...]"
	  " [-x world_x] [-y world_y] [-c max_clients]"
	  " [-t speed] -n team_name_1 team_name_2 ...\n", av[0]);
  return (EXIT_FAILURE);
}

static int	check_team_names(t_list *list, char *progname)
{
  t_list	*tmp;
  t_list	*team_names;

  team_names = list;
  while (list)
    {
      tmp = team_names;
      while (tmp)
	{
	  if (tmp != list && !strcmp(tmp->data, list->data))
	    {
	      fprintf(stderr, "%s: each team-name "
		      "must be unique\n", progname);
	      return (EXIT_FAILURE);
	    }
	  tmp = tmp->next;
	}
      list = list->next;
    }
  return (EXIT_SUCCESS);
}

static int	check_options(t_server *server, int ac, char *av[])
{
  if (ac == 1 || ac > optind)
    return (usage(av));
  if (!server->listener && listen_on_port(server, "4242", SOCK_STREAM))
    return (EXIT_FAILURE);
  if (list_size(server->game.team_names) <= 1)
    {
      fprintf(stderr, "%s: you must create at least two teams\n", av[0]);
      return (EXIT_FAILURE);
    }
  return (check_team_names(server->game.team_names, av[0]));
}

static int	add_numbers(char c, t_server *server, char *arg)
{
  int		nb;

  if (c == 't' || c == 'c' || c == 'x' || c == 'y')
    {
      if ((nb = atoi(arg)) <= 0)
	{
	  fprintf(stderr, "./zappy: '-%c' requires a positive number\n", c);
	  return (EXIT_FAILURE);
	}
      if (c == 't')
	server->game.time = nb;
      if (c == 'c')
	server->game.max_cli = nb;
      if (c == 'x')
	server->game.width = nb;
      if (c == 'y')
	server->game.height = nb;
    }
  return (EXIT_SUCCESS);
}

int	parse_command_line(t_server *server, int ac, char *av[])
{
  char	c;

  server->game.team_names = NULL;
  server->game.width = 20;
  server->game.height = 20;
  server->game.time = 100;
  server->game.max_cli = 1;
  while ((c = getopt(ac, av, "p:x:y:c:t:n:")) != -1)
    {
      if (c == '?')
	return (EXIT_FAILURE);
      if (c == 'p' && listen_on_port(server, optarg, SOCK_STREAM))
	return (EXIT_FAILURE);
      if (add_numbers(c, server, optarg))
	return (EXIT_FAILURE);
      if (c == 'n')
	{
	  add_to_list(&(server->game.team_names), optarg);
	  while (optind < ac && av[optind][0] != '-')
	    add_to_list(&(server->game.team_names), av[optind++]);
	}
    }
  return (check_options(server, ac, av));
}
