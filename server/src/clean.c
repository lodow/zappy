/*
** clean.c for clean.c in /home/bridou_n/projets/zappy/server
**
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Thu May 22 16:44:51 2014 Nicolas Bridoux
** Last update Sat Jul 12 20:35:09 2014 Nicolas Bridoux
*/

#include "server.h"

void		free_instr(t_server *serv)
{
  t_list	*tmp;
  t_instr	*instr;

  tmp = serv->instr;
  while (tmp)
    {
      instr = (t_instr *)tmp->data;
      if (instr->cmd && strcmp(instr->cmd, "life") &&
	  strcmp(instr->cmd, "timeout"))
	free(instr->cmd);
      tmp = tmp->next;
    }
  rm_list(serv->instr, &free);
  serv->instr = NULL;
}

static void	free_eggs_and_map(t_server *serv)
{
  t_list	*tmp;
  size_t		i;

  tmp = serv->game.eggs;
  while (tmp)
    {
      free(((t_egg *)tmp->data)->teamname);
      tmp = tmp->next;
    }
  rm_list(serv->game.eggs, &free);
  serv->game.eggs = NULL;
  i = 0;
  while (serv->map && i < serv->game.height)
    free(serv->map[i++]);
  free(serv->map);
  serv->map = NULL;
  return (free_instr(serv));
}

void		quit_server(t_server *serv)
{
  t_list	*tmp;
  t_selfd	*tmpfd;

  tmp = serv->watch;
  while (tmp)
    {
      if ((tmpfd = (t_selfd *)tmp->data))
        {
	  if (tmpfd->callback == (void *)&handle_client)
	    {
	      free(((t_client *)tmpfd->data)->teamname);
	      free(((t_client *)tmpfd->data)->sock);
	      rm_list(((t_client *)tmpfd->data)->cmds, &free);
	      free(tmpfd->data);
	    }
	  destroy_ring_buffer(tmpfd->rbuff);
	  destroy_ring_buffer(tmpfd->wbuff);
          free(tmpfd);
        }
      tmp = tmp->next;
    }
  free(serv->cmd);
  rm_list(serv->watch, NULL);
  rm_list(serv->game.teams, &free);
  return (free_eggs_and_map(serv));
}

static void	fail_incant(t_server *serv, t_selfd *fd)
{
  pie(serv, fd, KO);
  send_to_everyone_on_square(serv, ((t_client *)fd->data)->x,
			     ((t_client *)fd->data)->y, "ko");
}

void		clean_client(t_server *serv, t_selfd *fd)
{
  t_list	*tmp;
  t_instr	*instr;

  tmp = serv->instr;
  while (tmp)
    {
      instr = tmp->data;
      if (instr && instr->fd == fd)
	{
	  if (instr->cmd && !strcmp(instr->cmd, "incantation"))
	    fail_incant(serv, fd);
	  if (instr->cmd && strcmp(instr->cmd, "life") &&
	      strcmp(instr->cmd, "timeout"))
	    free(instr->cmd);
	  rm_from_list(&serv->instr, tmp, &free);
	  tmp = serv->instr;
	}
      else
	tmp = tmp->next;
    }
  free(((t_client *)fd->data)->teamname);
  rm_list(((t_client *)fd->data)->cmds, &free);
  free(fd->data);
  rm_from_list(&(serv->watch), find_in_list(serv->watch, fd), &destroy_fd);
}
