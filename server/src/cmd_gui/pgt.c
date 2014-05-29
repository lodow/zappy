/*
** pgt.c for pgt in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:44:48 2014 Nicolas Bridoux
** Last update Fri May 30 00:45:12 2014 Nicolas Bridoux
*/

#include "server.h"

void	pgt(t_server *serv, size_t cli_num, int ressource_num)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "pgt %zu %d", cli_num, ressource_num);
  send_to_every_gui(serv, buff);
}
