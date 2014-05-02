/*
** log.c for log.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May  1 16:35:58 2014 Nicolas Bridoux
** Last update Thu May  1 18:05:48 2014 Nicolas Bridoux
*/

#include "server.h"

void		server_log(char warn_level, const char *fmt, ...)
{
  va_list	ap;

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

void		display_start(t_server *server)
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
  tmp = server->game.team_names;
  while (tmp)
    {
      printf("\t%s%s%s\t\t (%s%zu%s)\n", YELLOW, (char *)tmp->data,
	     WHITE, GREEN, server->game.max_cli, WHITE);
      tmp = tmp->next;
    }
  printf("Generating world...%sdone%s\n\n", GREEN, WHITE);

  server_log(WARNING, "Warning message");
  server_log(ERROR, "Error message");
  server_log(SENDING, "Sending some data");
  server_log(RECEIVING, "Receiving some data");
}
