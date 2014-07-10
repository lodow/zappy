/*
** kick.c for kick.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri Jul  4 10:18:19 2014 Nicolas Bridoux
** Last update Fri Jul  4 10:32:50 2014 Nicolas Bridoux
*/

#include "server.h"

void		kick(t_server *serv, char **args)
{
  t_list	*tmp;
  t_selfd	*fd;
  size_t	nb;

  if (!args[0])
    {
      printf("%susage : kick __num_player__\n%s", RED, WHITE);
      return ;
    }
  nb = atoi(args[0]);
  tmp = serv->watch;
  while (tmp)
    {
      fd = (t_selfd *)tmp->data;
      if (fd->callback == (void *)&handle_client && nb == fd->cli_num)
	{
	  printf("%s%zu : player succesfully kiked.\n%s", GREEN, nb, WHITE);
	  send_response(fd, "you were kicked from the server.");
	  fd->to_close = 1;
	  return ;
	}
      tmp = tmp->next;
    }
  printf("%s%zu : player not found.\n%s", RED, nb, WHITE);
}
