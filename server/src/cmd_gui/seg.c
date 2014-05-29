/*
** seg.c for seg.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 30 00:55:04 2014 Nicolas Bridoux
** Last update Fri May 30 00:55:56 2014 Nicolas Bridoux
*/

#include "server.h"

void	seg(t_server *serv, char *win)
{
  char	buff[BUFF_SIZE];

  snprintf(buff, sizeof(buff), "seg %s", win);
  send_to_every_gui(serv, buff);
}
