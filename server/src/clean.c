/*
** clean.c for clean.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 22 16:44:51 2014 Nicolas Bridoux
** Last update Fri May 30 18:10:06 2014 Nicolas Bridoux
*/

#include "server.h"

static void	free_eggs_and_map(t_server *serv)
{
  t_list	*tmp;
  size_t       	i;

  tmp = serv->game.eggs;
  while (tmp)
    {
      free(((t_egg *)tmp->data)->teamname);
      tmp = tmp->next;
    }
  rm_list(serv->game.eggs, &free);
  i = 0;
  while (serv->map && i < serv->game.height)
    free(serv->map[i++]);
  free(serv->map);
}

void		quit_server(t_server *serv)
{
  t_list	*tmp;
  t_selfd	*tmpfd;

  tmp = serv->watch;
  while (tmp)
    {
      if ((tmpfd = (t_selfd*)tmp->data))
        {
          free(tmpfd->data);
          free(tmpfd);
        }
      tmp = tmp->next;
    }
  rm_list(serv->game.teams, &free);
  return (free_eggs_and_map(serv));
}

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
  free(fd->rb_r);
  free(fd->rb_w);
  rm_from_list(&(serv->watch), find_in_list(serv->watch, fd), &free);
}
