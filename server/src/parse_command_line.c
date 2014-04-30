/*
** parse_command_line.c for parse_command_line.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed Apr 30 17:20:06 2014 Nicolas Bridoux
** Last update Wed Apr 30 18:37:34 2014 Nicolas Bridoux
*/

#include "server.h"

static int	usage(char *av[])
{
  fprintf(stderr, "usage: %s [[[-p port] -p port] ...]"
	  " [-x world_x] [-y world_y] [-c max_clients]"
	  " [-t speed] -n team_name_1 team_name_2 ...\n", av[0]);
  return (EXIT_FAILURE);
}

static int	check_options(t_server *server)
{
  if (!server->listener && listen_on_port(server, "4242", SOCK_STREAM))
    return (EXIT_FAILURE);
  // check nb_teams
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
      if (c == 'x')
	server->game.width = atoi(optarg);
      if (c == 'y')
	server->game.height = atoi(optarg);
      if (c == 'n')
	{
	  printf("optind = %d\n", optind);
	  add_to_list(&(server->game.team_names), optarg);
	}
    }
  return (check_options(server));
}
