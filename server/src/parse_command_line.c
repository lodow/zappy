/*
** parse_command_line.c for parse_command_line.c in /home/bridou_n/projets/zappy/server
**
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Wed Apr 30 17:20:06 2014 Nicolas Bridoux
** Last update Mon May 19 23:17:15 2014 Nicolas Bridoux
*/

#include "server.h"

static int	check_team_names(t_list *list, char *progname,
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

static int	check_options(t_server *server, int ac, char *av[])
{
  if (ac == 1 || ac > optind)
    {
      fprintf(stderr, "usage: %s [[[-p port] -p port] ...]"
	      " [-x world_x] [-y world_y] [-c max_clients]"
	      " [-t speed] -n team_name_1 team_name_2 ...\n", av[0]);
      return (EXIT_FAILURE);
    }
  if (!server->listener && listen_on_port(server, "4242", SOCK_STREAM))
    return (EXIT_FAILURE);
  if (list_size(server->game.teams) <= 1)
    {
      fprintf(stderr, "%s: you must create at least two teams\n", av[0]);
      return (EXIT_FAILURE);
    }
  return (check_team_names(server->game.teams, av[0], server));
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
	server->game.time = USEC(1) / nb;
      if (c == 'c')
	server->game.max_cli = nb;
      if (c == 'x')
	server->game.width = nb;
      if (c == 'y')
	server->game.height = nb;
    }
  return (EXIT_SUCCESS);
}

static void	init_serv(t_server *server)
{
  server->game.teams = NULL;
  server->game.width = 20;
  server->game.height = 20;
  server->game.time = 100;
  server->game.max_cli = 1;
  server->game.cli_num = 1;
}

int		parse_command_line(t_server *server, int ac, char *av[])
{
  char		c;
  t_team	*t;

  init_serv(server);
  while ((c = getopt(ac, av, "p:x:y:c:t:n:")) != -1)
    {
      if (c == '?')
	return (EXIT_FAILURE);
      if (c == 'p' && listen_on_port(server, optarg, SOCK_STREAM))
	return (EXIT_FAILURE);
      if (add_numbers(c, server, optarg))
	return (EXIT_FAILURE);
      if (c == 'n' && (t = malloc(sizeof(t_team))))
	{
	  t->name = optarg;
	  t->max_cli = server->game.max_cli;
	  add_to_list(&(server->game.teams), t);
	  while (optind < ac && av[optind][0] != '-' && (t = malloc(sizeof(t_team))))
	    {
	      t->name = av[optind++];
	      t->max_cli = server->game.max_cli;
	      add_to_list(&(server->game.teams), t);
	    }
	}
    }
  return (check_options(server, ac, av));
}
