/*
** pic.c for pic.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 29 23:47:20 2014 Nicolas Bridoux
** Last update Fri May 30 00:09:06 2014 Nicolas Bridoux
*/

#include "server.h"

static char	*get_all_players_number(t_server *serv, t_selfd *fd,
					char *buff)
{
  t_list	*tmp;
  t_selfd	*fd_cli;
  t_client	*him;
  char		nb[BUFF_SIZE];

  tmp = serv->watch;
  while (tmp)
    {
      fd_cli = (t_selfd *)tmp->data;
      if (fd_cli != fd && fd_cli->callback == (void *)&handle_client)
	{
	  him = (t_client *)fd->data;
	  if (him->type_cli == IA && ((t_client *)fd->data)->x == him->x &&
	      ((t_client *)fd->data)->y == him->y)
	    {
	      snprintf(nb, sizeof(nb), " %zu", fd_cli->cli_num);
	      buff = concat(buff, nb);
	    }
	}
      tmp = tmp->next;
    }
  return (buff);
}

void		pic(t_server *serv, t_selfd *fd)
{
  char		tmp[BUFF_SIZE];
  char		*buff;
  t_client	*client;

  client = (t_client *)fd->data;
  snprintf(tmp, sizeof(tmp), "pic %zu %zu %d %zu",
	   client->x, client->y, client->level, fd->cli_num);
  buff = strdup(tmp);
  buff = get_all_players_number(serv, fd, buff);
  if (!buff)
    return ;
  send_to_every_gui(serv, buff);
  free(buff);
}
