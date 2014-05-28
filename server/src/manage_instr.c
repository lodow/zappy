/*
** manage_instr.c for manage_instr.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 22 11:02:39 2014 Nicolas Bridoux
** Last update Wed May 28 11:12:45 2014 Nicolas Bridoux
*/

#include "server.h"

static void	handle_special_timeout(t_server *serv, t_selfd *fd, char *cmd)
{
  t_client	*client;

  if (!fd)
    return (handle_eggs(serv, cmd));
  client = (t_client *)fd->data;
  if (!strcmp(cmd, "timeout") && client->type_cli == UNKNOWN)
    close_connection(serv, fd);
  if (!strcmp(cmd, "life"))
    {
      if (client->inv.food > 0)
	{
	  --(client->inv.food);
	  set_timeout(serv, fd, "life", 126 * (USEC(1) / serv->game.time));
	}
      else
	{
	  send_response(fd, "mort");
	  fd->to_close = 1;
	}
    }
}

void			exec_instruction(t_server *serv)
{
  struct timeval	now;
  t_instr		*next;

  gettimeofday(&now, NULL);
  now.tv_usec += USEC(now.tv_sec);
  if (serv->instr && (next = (t_instr *)serv->instr->data))
    {
      if (next->time <= now.tv_usec)
	{
	  if (!strcmp(next->cmd, "timeout") || !strcmp(next->cmd, "life") ||
	      !strncmp(next->cmd, "born:", 5) || !strncmp(next->cmd, "moldy:", 6))
	    {
	      handle_special_timeout(serv, next->fd, next->cmd);
	      rm_from_list(&(serv->instr), serv->instr, &free);
	      return ;
	    }
	  exec_cmd(serv, next->fd, next->cmd);
	  ((t_client *)next->fd->data)->flag = OK;
	  rm_from_list(&(serv->instr), serv->instr, &free);
	}
    }
}

void		push_instruction(t_server *serv, t_selfd *fd)
{
  t_client	*client;
  t_list	*cmd;
  float		delay;

  if (fd && fd->callback == (void *)&handle_client)
    {
      client = (t_client *)fd->data;
      if (client->flag == OK && client->cmds && client->type_cli == IA)
	{
	  if ((cmd = dequeue(&(client->cmds))) &&
	      (delay = is_cmd_valid(serv, fd, (char *)cmd->data)) >= 0)
	    {
	      set_timeout(serv, fd, (char *)cmd->data,
			  USEC(delay / (float)serv->game.time));
	      client->flag = KO;
	    }
	  free(cmd);
	}
    }
}
