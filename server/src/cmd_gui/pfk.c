/*
** pfk.c for pfk.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:33:11 2014 Nicolas Bridoux
** Last update Fri May 30 00:34:22 2014 Nicolas Bridoux
*/

#include "server.h"

void   	pfk(t_server *serv, t_selfd *fd)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "pfk %zu", fd->cli_num);
  send_to_every_gui(serv, buff);
}
