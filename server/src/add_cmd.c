/*
** exec_cmd.c for exec_cmd.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue Apr 29 21:13:41 2014 Nicolas Bridoux
** Last update Tue May 20 12:07:38 2014 Nicolas Bridoux
*/

#include "server.h"

static void	connect_gui(__attribute__((unused))t_server *serv, t_selfd *fd)
{
  t_client	*client;

  client = (t_client *)fd->data;
  client->type_cli = GUI;

  client->action = NO_ACTION; // on annule le timeout
  // envoyer la map au client
}

static int	init_ia(t_server *serv, t_client *client, char *cmd)
{
  client->type_cli = IA;
  client->teamname = strdup(cmd);
  client->x = rand() % serv->game.width;
  client->y = rand() % serv->game.height;
  client->orientation = rand() % 4;
  memset(&(client->inv), 0, sizeof(t_map));
  client->inv.food = 10;

  client->action = NO_ACTION;
  set_timeout(client, LIFE, 126 * (USEC(1) / serv->game.time));
  return (0);
}

static int	connect_ia(t_server *serv, t_selfd *fd, char *cmd)
{
  char		buff[BUFF_SIZE];
  t_list	*tmp;

  tmp = serv->game.teams;
  while (tmp)
    {
      if (!strcmp(((t_team *)tmp->data)->name, cmd))
	{
	  if (!((t_team *)tmp->data)->max_cli)
	    return (NOT_ALLOWED);
	  snprintf(buff, sizeof(buff), "%zu", --((t_team *)tmp->data)->max_cli);
	  send_response(fd, buff);
	  snprintf(buff, sizeof(buff), "%zu %zu",
		   serv->game.width, serv->game.height);
	  send_response(fd, buff);
	  return (init_ia(serv, ((t_client *)fd->data), cmd));
	}
      tmp = tmp->next;
    }
  return (NOT_KNOWN);
}

static void	first_message(t_server *serv, t_selfd *fd, char *cmd)
{
  int		err;

  if (!strcmp(cmd, "GRAPHIC"))
    return (connect_gui(serv, fd));
  err = connect_ia(serv, fd, cmd);
  if (err)
    {
      send_response(fd, "ko");
      fd->to_close = 1;
      server_log(WARNING, (err == NOT_ALLOWED) ?
		 "No more connections allowed for \"%s\"" :
		 "\"%s\": team-name not found", cmd);
    }
  else
    server_log(WARNING, "Added new player %zu at (%zu, %zu)", fd->cli_num,
	       ((t_client *)fd->data)->x, ((t_client *)fd->data)->y);
}

void		handle_add_cmd(t_server *server, t_selfd *fd, char *cmd)
{
  t_client	*client;

  client = (t_client *)fd->data;
  if (client->type_cli == UNKNOWN)
    {
      first_message(server, fd, cmd);
      free(cmd);
    }
  else
    enqueue(&((t_client *)fd->data)->cmds, cmd);
}
