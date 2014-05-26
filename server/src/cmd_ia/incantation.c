/*
** incantation.c for incantation.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Sat May 24 20:03:06 2014 Nicolas Bridoux
** Last update Tue May 27 00:40:23 2014 Nicolas Bridoux
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
	  if (client->x == x && client->y == y)
	    ++nb;
	}
      tmp = tmp->next;
    }
  return (nb);
}

int		check_incant(t_server *serv, t_selfd *fd)
{
  t_client	*client;
  t_map		square;
  int		ret;

  client = (t_client *)fd->data;
  if (client->level >= 8)
    return (0);
  square = serv->map[client->y][client->x];
  square.food = nb_players_at(serv, client->x, client->y);
  ret = !memcmp(&square, &g_incant[(size_t)client->level], sizeof(t_map));
  if (ret)
    // envoyer élévation en cours à tous
  return (ret);
}

void		incantation(t_server *serv, t_selfd *fd,
		     __attribute__((unused))char **args)
{
  // check_incant de nouveau


}
