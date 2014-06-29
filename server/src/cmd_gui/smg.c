/*
** smg.c for smg.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:56:40 2014 Nicolas Bridoux
** Last update Fri May 30 00:57:35 2014 Nicolas Bridoux
*/

#include "server.h"

void	smg(t_server *serv, char *msg)
{
  char	*buff;

  buff = strdup("smg ");
  buff = concat(buff, msg);
  send_to_every_gui(serv, buff);
  free(buff);
}
