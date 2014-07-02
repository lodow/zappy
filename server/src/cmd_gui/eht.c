/*
** eht.c for eht.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:49:05 2014 Nicolas Bridoux
** Last update Fri May 30 00:50:26 2014 Nicolas Bridoux
*/

#include "server.h"

void	eht(t_server *serv, size_t num_egg)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "eht %zu", num_egg);
  send_to_every_gui(serv, buff);
}
