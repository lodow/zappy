/*
** parse_command_line.c for parse_command_line.c in /home/bridou_n/projets/zappy/server
**
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Wed Apr 30 17:20:06 2014 Nicolas Bridoux
** Last update Sat May 31 17:13:41 2014 Nicolas Bridoux
*/

#include "server.h"

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

static void	init_serv(t_server *server)
{
  server->game.teams = NULL;
  server->game.eggs = NULL;
  server->instr = NULL;
  server->game.width = 20;
  server->game.height = 20;
  server->game.time = 100;
  server->game.max_cli = 1;
  server->game.cli_num = 1;
}

static void	add_team_names(t_team *t, t_server *server, int ac, char *av[])
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
	add_team_names(t, server, ac, av);
    }
  return (check_options(server, ac, av));
}
