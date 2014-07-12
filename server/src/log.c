/*
** log.c for log.c in /home/bridou_n/projets/zappy/server
**
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Thu May  1 16:35:58 2014 Nicolas Bridoux
** Last update Sat Jul 12 20:14:17 2014 Nicolas Bridoux
*/

#include "server.h"

extern t_server g_serv;

void		server_log(char warn_level, const char *fmt, ...)
{
  va_list	ap;

  if (!g_serv.debug)
    return ;
  va_start(ap, fmt);
  if (warn_level == WARNING)
    printf("%s*** ", YELLOW);
  if (warn_level == ERROR)
    printf("%s!!! ", RED);
  if (warn_level == SENDING)
    printf("%s>>> ", BLUE);
  if (warn_level == RECEIVING)
    printf("%s<<< ", GREEN);
  vprintf(fmt, ap);
  printf("%s\n", WHITE);
  va_end(ap);
}

static void	display_start(t_server *server)
{
  t_list	*tmp;

  serv_verbose(server);
  printf("\nConfiguration: max_cli(%s%zu%s), map_x(%s%zu%s), "
         "map_y(%s%zu%s), time(%s%zu%s)\n",
         GREEN, server->game.max_cli, WHITE,
         GREEN, server->game.width, WHITE,
         GREEN, server->game.height, WHITE,
         GREEN, server->game.time, WHITE);
  printf("Teams:");
  tmp = server->game.teams;
  while (tmp)
    {
      printf("\t%s%s%s\t\t (%s%zu%s)\n", YELLOW, ((t_team *)tmp->data)->name,
             WHITE, GREEN, ((t_team *)tmp->data)->max_cli, WHITE);
      tmp = tmp->next;
    }
  printf("Generating world...");
  fflush(stdout);
}

static int	gen_world(t_server *server)
{
  size_t	y;
  size_t	x;

  if (!(server->map = malloc(sizeof(t_map *) * (server->game.height + 1))))
    return (EXIT_FAILURE);
  y = 0;
  while (y < server->game.height)
    {
      x = 0;
      if (!(server->map[y] = malloc(sizeof(t_map) * (server->game.width))))
        return (EXIT_FAILURE);
      while (x < server->game.width)
        memset(&(server->map[y][x++]), 0, sizeof(t_map));
      ++y;
    }
  gen_ressource(server, "linemate", AREA / 2 + DEMI_PERIMETER / 2, 0);
  gen_ressource(server, "deraumere", AREA / 3 + DEMI_PERIMETER / 2, 0);
  gen_ressource(server, "sibur", AREA / 4 + DEMI_PERIMETER / 2, 0);
  gen_ressource(server, "mendiane", AREA / 6 + DEMI_PERIMETER / 2, 0);
  gen_ressource(server, "phiras", AREA / 8 + DEMI_PERIMETER / 2, 0);
  gen_ressource(server, "thystame", AREA / 10 + DEMI_PERIMETER / 2, 0);
  return (EXIT_SUCCESS);
}

int	handle_start(t_server *server)
{
  display_start(server);
  if (gen_world(server))
    {
      printf("%serror (not enough memory), exiting%s\n\n", RED, WHITE);
      return (EXIT_FAILURE);
    }
  printf("%sdone%s\n\n", GREEN, WHITE);
  if (isatty(STDIN_FILENO))
    {
      help(NULL, NULL);
      printf("\n%s", PROMPT);
    }
  else
    printf("%s", "Running in non interactive mode\n");
  fflush(stdout);
  return (EXIT_SUCCESS);
}
