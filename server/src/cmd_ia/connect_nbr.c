/*
** connect_nbr.c for connect_nbr.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 23:40:45 2014 Nicolas Bridoux
** Last update Fri May 30 18:49:38 2014 Nicolas Bridoux
*/

#include "server.h"

void		connect_nbr(t_server *serv, t_selfd *fd,
			    __attribute__((unused))char **args)
{
  t_list	*tmp;
  t_client	*client;
  char		buff[BUFF_SIZE];

  client = (t_client *)fd->data;
  tmp = serv->game.teams;
  while (tmp)
    {
      if (client->teamname && ((t_team *)tmp->data)->name &&
	  !strcmp(((t_team *)tmp->data)->name, client->teamname))
	{
	  snprintf(buff, sizeof(buff), "%zu", ((t_team *)tmp->data)->max_cli);
	  send_response(fd, buff);
	}
      tmp = tmp->next;
    }
}
