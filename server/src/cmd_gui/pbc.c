/*
** pbc.c for pbc.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 29 23:42:21 2014 Nicolas Bridoux
** Last update Thu May 29 23:45:43 2014 Nicolas Bridoux
*/

#include "server.h"

void		pbc(t_server *serv, t_selfd *fd, char *msg)
{
  char		*buff;
  size_t	len;

  if (!msg)
    return ;
  len = strlen(msg);
  if (!(buff = malloc(sizeof(char) * (len + 50))))
    return ;
  snprintf(buff, len + 50, "pbc %zu %s", fd->cli_num, msg);
  send_to_every_gui(serv, buff);
  free(buff);
}

