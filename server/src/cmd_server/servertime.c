/*
** servertime.c for servertime.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri Jul  4 09:43:12 2014 Nicolas Bridoux
** Last update Thu Jul 10 21:39:56 2014 Nicolas Bridoux
*/

#include "server.h"

void		servertime(t_server *serv, char **args)
{
  suseconds_t	time;
  char		buff[BUFF_SIZE];

  time = -1;
  if (!args[0])
    {
      printf("%susage : servertime __new_time__\n%s", RED, WHITE);
      return ;
    }
  if (args[0] && (time = atoi(args[0])) > 0)
    {
      serv->game.time = time;
      printf("%sServertime successfully changed to : %ld\n%s",
	     GREEN, serv->game.time, WHITE);
      snprintf(buff, sizeof(buff), "sgt %zu", serv->game.time);
      send_to_every_gui(serv, buff);
      return ;
    }
  printf("%sServertime must be a positive number (%ld given).\n%s",
	 RED, time, WHITE);
}
