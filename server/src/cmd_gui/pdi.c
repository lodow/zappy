/*
** pdi.c for pdi.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:46:36 2014 Nicolas Bridoux
** Last update Fri May 30 00:48:01 2014 Nicolas Bridoux
*/

#include "server.h"

void	pdi(t_server *serv, size_t num_cli)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "pdi %zu", num_cli);
  send_to_every_gui(serv, buff);
}
