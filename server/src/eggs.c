/*
** eggs.c for eggs.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Sat May 24 01:42:18 2014 Nicolas Bridoux
** Last update Sat Jun  7 14:32:40 2014 Nicolas Bridoux
*/

#include "server.h"

t_egg		*find_egg(t_list *list, int num_egg,
			  char state, char *teamname)
{
  t_egg		*egg;

  while (list)
    {
      egg = (t_egg *)list->data;
      if (egg->state == state)
	{
	  if (!teamname && (int)egg->num_egg == num_egg)
	    return (egg);
	  if (num_egg == -1 && egg->teamname && teamname &&
	      !strcmp(egg->teamname, teamname))
	    return (egg);
	}
      list = list->next;
    }
  return (NULL);
}

static void	egg_hatched(t_server *serv, char *cmd)
{
  t_egg		*egg;
  t_list	*tmp;
  char		buff[BUFF_SIZE];

  if ((egg = find_egg(serv->game.eggs, atoi(&cmd[5]), TO_BORN, NULL)))
    {
      server_log(WARNING, "Egg %zu is hatch in (%d,%d)",
		 egg->num_egg, egg->x, egg->y);
      gen_food(serv);
      eht(serv, egg->num_egg);
      tmp = serv->game.teams;
      while (tmp)
	{
	  if (egg->teamname && tmp->data && ((t_team *)tmp->data)->name &&
	      !strcmp(((t_team *)tmp->data)->name, egg->teamname))
	    ++(((t_team *)tmp->data)->max_cli);
	  tmp = tmp->next;
	}
      egg->state = ALIVE;
      snprintf(buff, sizeof(buff), "moldy:%zu", egg->num_egg);
      set_timeout(serv, NULL, strdup(buff),
		  USEC((float)MOLDY_TIME / (float)serv->game.time));
    }
}

void	handle_eggs(t_server *serv, char *cmd)
{
  t_egg	*egg;

  if (cmd && !strncmp(cmd, "born:", 5))
    {
      egg_hatched(serv, cmd);
      free(cmd);
      cmd = NULL;
    }
  if (cmd && !strncmp(cmd, "moldy:", 6))
    {
      if ((egg = find_egg(serv->game.eggs, atoi(&cmd[6]), ALIVE, NULL)))
	{
	  server_log(WARNING, "Egg %zu is moldy (%d,%d)...",
		     egg->num_egg, egg->x, egg->y);
	  edi(serv, egg->num_egg);
	  free(egg->teamname);
	  rm_from_list(&(serv->game.eggs),
		       find_in_list(serv->game.eggs, egg), &free);
	}
      free(cmd);
    }
}

void		replace_egg_by_ia(t_server *serv, t_selfd *fd, t_egg *egg)
{
  t_client	*client;

  client = (t_client *)fd->data;
  client->x = egg->x;
  client->y = egg->y;
  free(egg->teamname);
  server_log(WARNING, "Player %zu takes over egg %zu",
	     fd->cli_num, egg->num_egg);
  ebo(serv, egg->num_egg);
  fd->cli_num = egg->num_egg;
  --serv->game.cli_num;
  rm_from_list(&(serv->game.eggs),
	       find_in_list(serv->game.eggs, egg), &free);
}
