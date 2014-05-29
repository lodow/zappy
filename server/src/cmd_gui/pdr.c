/*
** pdr.c for pdr.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:42:03 2014 Nicolas Bridoux
** Last update Fri May 30 00:45:01 2014 Nicolas Bridoux
*/

#include "server.h"

void	pdr(t_server *serv, size_t cli_num, int ressource_num)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "pdr %zu %d", cli_num, ressource_num);
  send_to_every_gui(serv, buff);
}
