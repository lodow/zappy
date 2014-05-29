/*
** ebo.c for ebo.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 29 23:09:25 2014 Nicolas Bridoux
** Last update Fri May 30 00:53:13 2014 Nicolas Bridoux
*/

#include "server.h"

void	ebo(t_server *serv, size_t num_egg)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "ebo %zu", num_egg);
  send_to_every_gui(serv, buff);
}
