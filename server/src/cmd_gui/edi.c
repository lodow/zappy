/*
** edi.c for edi.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:51:36 2014 Nicolas Bridoux
** Last update Fri May 30 00:53:19 2014 Nicolas Bridoux
*/

#include "server.h"

void	edi(t_server *serv, size_t num_egg)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "edi %zu", num_egg);
  send_to_every_gui(serv, buff);
}
