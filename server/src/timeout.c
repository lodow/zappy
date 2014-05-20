/*
** timeout.c for timeout.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Mon May 19 20:49:41 2014 Nicolas Bridoux
** Last update Tue May 20 14:54:30 2014 Nicolas Bridoux
*/

#include "server.h"

/*
** set "type" timeout for "client", for "time" usecs
*/

void			set_timeout(t_client *client, char type, suseconds_t time)
{
  struct timeval	t;

  gettimeofday(&t, NULL);
  if (type == LIFE)
    client->life = USEC(t.tv_sec + (time / 1000000)) +
      t.tv_usec + time % 1000000;
  else
    client->action = USEC(t.tv_sec + (time / 1000000)) +
      t.tv_usec + time % 1000000;
}

/*
** check if there is a timeout for an action, set it if it's the case
*/

static int	timeout_cmd(struct timeval *now, t_selfd *fd,
			    t_client *client, t_server *serv)
{
  t_list	*cmd;
  int		delay;

  if (client->cmds && client->action == NO_ACTION && client->type_cli != UNKNOWN)
    {
      if ((cmd = top(client->cmds)))
	{
	  if ((delay = is_cmd_valid(fd, (char *)cmd->data)) >= 0)
	    {
	      server_log(WARNING, "Setting delay of %ld for %d",
			 USEC(delay / serv->game.time), fd->cli_num);
	      set_timeout(client, ACTION, USEC(delay / serv->game.time));
	    }
	}
    }
  if (client->action != NO_ACTION && client->action <= USEC(now->tv_sec) + now->tv_usec)
    {
      if (!(cmd = dequeue(&(client->cmds))))
	{
	  close_connection(serv, fd);
	  return (EXIT_FAILURE);
	}
      // executer la cmd
      client->action = NO_ACTION;
    }
  return (EXIT_SUCCESS);
}

/*
** check if the client is still alive and set his next life timeout
*/

static void	timeout_life(struct timeval *now, t_selfd *fd,
			     t_client *client, t_server *serv)
{
  if (client->type_cli == IA &&
      client->life != NO_ACTION &&
      client->life <= USEC(now->tv_sec) + now->tv_usec)
    {
      if (client->inv.food)
	{
	  --client->inv.food;
	  server_log(WARNING, "Player %d lost 1 food (%zu remaining)",
		     fd->cli_num, client->inv.food);
	  set_timeout(client, LIFE, 126 * (USEC(1) / serv->game.time));
	}
      else
	{
	  send_response(fd, "mort");
	  fd->to_close = 1;
	  client->life = NO_ACTION;
	  client->action = NO_ACTION;
	}
    }
}

/*
** this function handle the life and command timeouts
** it's called by every client fd
*/

void			handle_timeout(t_server *serv, t_selfd *fd)
{
  struct timeval	now;
  t_client		*client;

  client = (t_client *)fd->data;
  gettimeofday(&now, NULL);
  if (!timeout_cmd(&now, fd, client, serv))
    timeout_life(&now, fd, client, serv);
}
