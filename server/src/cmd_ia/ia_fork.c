/*
** ia_fork.c for ia_fork.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 23 22:49:40 2014 Nicolas Bridoux
** Last update Fri May 30 01:14:29 2014 Nicolas Bridoux
*/

#include "server.h"

void		ia_fork(t_server *serv, t_selfd *fd,
			__attribute__((unused))char **args)
{
  t_client	*client;
  t_egg		*new_egg;
  char		buff[BUFF_SIZE];

  client = (t_client *)fd->data;
  server_log(WARNING, "Egg %zu was laid in (%d,%d)",
	     serv->game.cli_num, client->x, client->y);
  enw(serv, serv->game.cli_num, fd);
  if ((new_egg = malloc(sizeof(t_egg))))
    {
      new_egg->num_egg = serv->game.cli_num++;
      new_egg->teamname = client->teamname ? strdup(client->teamname) : NULL;
      new_egg->x = client->x;
      new_egg->y = client->y;
      new_egg->state = TO_BORN;
      new_egg->father = fd->cli_num;
      add_to_list(&(serv->game.eggs), new_egg);
      snprintf(buff, sizeof(buff), "born:%zu", new_egg->num_egg);
      set_timeout(serv, NULL, strdup(buff),
		  USEC((float)600 / (float)serv->game.time));
      return (send_response(fd, "ok"));
    }
  send_response(fd, "ko");
}
