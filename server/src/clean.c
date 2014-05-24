/*
** clean.c for clean.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 22 16:44:51 2014 Nicolas Bridoux
** Last update Fri May 23 23:20:04 2014 Nicolas Bridoux
*/

#include "server.h"

void		clean_client(t_server *serv, t_selfd *fd)
{
  t_list	*tmp;

  tmp = serv->instr;
  while (tmp)
    {
      if (((t_instr *)tmp->data)->fd == fd)
	{
	  rm_from_list(&serv->instr, tmp, &free);
	  tmp = serv->instr;
	}
      else
	tmp = tmp->next;
    }
  display_serv_queue(serv);
  free(fd->rb_r);
  free(fd->rb_w);
  rm_from_list(&(serv->watch), find_in_list(serv->watch, fd), &free);
}
