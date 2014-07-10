/*
** shutdown.c for shutdown.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri Jul  4 10:54:35 2014 Nicolas Bridoux
** Last update Fri Jul  4 10:56:50 2014 Nicolas Bridoux
*/

#include "server.h"

void	serv_shutdown(t_server *serv, __attribute__((unused))char **args)
{
  printf("%sServer is shutting down...%s\n", GREEN, WHITE);
  serv->quit = 1;
}
