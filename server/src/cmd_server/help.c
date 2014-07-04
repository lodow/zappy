/*
** help.c for help.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri Jul  4 09:53:38 2014 Nicolas Bridoux
** Last update Fri Jul  4 16:01:04 2014 Nicolas Bridoux
*/

#include "server.h"

void	help(__attribute__((unused))t_server *serv,
	     __attribute__((unused))char **args)
{
  printf("%sservertime __time__ : change the "
	 "servertime to __time__\n", BLUE_BOLD);
  printf("kick __num_player__ : kick the player __num_player__\n");
  printf("resize __x_size__ __y_size__: resize the map to "
	 "be __x_size__ / __y_size__\n");
  printf("add __res_name__ __nb_ : add __nb__ units of "
	 "__res_name__ on the map_\n");
  printf("shutdown : disconnect every clients and shutdown the server\n");
  printf("help : display this help\n%s", WHITE);
}
