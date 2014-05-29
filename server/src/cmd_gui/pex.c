/*
** pex.c for pex.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 29 23:31:30 2014 Nicolas Bridoux
** Last update Thu May 29 23:38:52 2014 Nicolas Bridoux
*/

#include "server.h"

void	pex(t_server *serv, t_selfd *fd)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "pex %zu", fd->cli_num);
  send_to_every_gui(serv, buff);
}
