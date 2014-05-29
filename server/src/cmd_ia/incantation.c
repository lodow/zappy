/*
** incantation.c for incantation.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Sat May 24 20:03:06 2014 Nicolas Bridoux
** Last update Fri May 30 00:20:53 2014 Nicolas Bridoux
*/

#include "server.h"

static t_map	g_incant[] =
  {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
  };

size_t		nb_players_at(t_server *serv, size_t x, size_t y)
{
  t_list	*tmp;
  t_selfd	*fd_watch;
  t_client	*client;
  size_t	nb;

  nb = 0;
  tmp = serv->watch;
  while (tmp)
    {
      fd_watch = (t_selfd *)tmp->data;
      if (fd_watch->callback == (void *)&handle_client)
	{
	  client = (t_client *)fd_watch->data;
	  if (client->type_cli == IA && client->x == x && client->y == y)
	    ++nb;
	}
      tmp = tmp->next;
    }
  return (nb);
}

static void	send_to_everyone_on_square(t_server *serv, size_t x,
					   size_t y, char *msg)
{
  t_selfd	*fd;
  t_client	*him;
  t_list	*tmp;

  tmp = serv->watch;
  while (tmp)
    {
      fd = (t_selfd *)tmp->data;
      if (fd->callback == (void *)&handle_client)
	{
	  him = (t_client *)fd->data;
	  if (him->type_cli == IA && x == him->x && y == him->y)
	    send_response(fd, msg);
	}
      tmp = tmp->next;
    }
}

int		check_incant(t_server *serv, t_selfd *fd, char send)
{
  t_client	*me;
  t_map		square;
  int		ret;

  me = (t_client *)fd->data;
  if (me->level >= 8)
    return (0);
  square = serv->map[me->y][me->x];
  square.food = nb_players_at(serv, me->x, me->y);
  ret = !memcmp(&square, &g_incant[(size_t)me->level - 1], sizeof(t_map));
  if (ret && send == OK)
    {
      pic(serv, fd);
      send_to_everyone_on_square(serv, me->x, me->y, "elevation en cours");
    }
  return (ret);
}

static void	send_level_up(t_server *serv, t_client *client)
{
  t_list	*tmp;
  t_client	*him;
  t_selfd	*fd;
  char		buff[BUFF_SIZE];

  tmp = serv->watch;
  while (tmp)
    {
      fd = (t_selfd *)tmp->data;
      if (fd && fd->callback == (void *)&handle_client)
	{
	  him = (t_client *)fd->data;
	  if (him->type_cli == IA && him->x == client->x &&
	      him->y == client->y)
	    {
	      snprintf(buff, sizeof(buff), "niveau actuel : %d", ++him->level);
	      send_response(fd, buff);
	    }
	}
      tmp = tmp->next;
    }
}

void		incantation(t_server *serv, t_selfd *fd,
		     __attribute__((unused))char **args)
{
  if (!check_incant(serv, fd, KO))
    {
      pie(serv, fd, KO);
      send_response(fd, "ko");
    }
  else
    {
      pie(serv, fd, OK);
      send_level_up(serv, (t_client *)fd->data);
    }
}
