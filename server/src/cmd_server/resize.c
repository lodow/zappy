/*
** resize.c for  in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri Jul  4 15:32:15 2014 Nicolas Bridoux
** Last update Sat Jul 12 20:18:16 2014 Nicolas Bridoux
*/

#include "server.h"

static void	notify_gui(t_server *serv)
{
  t_list	*tmp;
  t_selfd	*fd;

  tmp = serv->watch;
  while (tmp)
    {
      fd = (t_selfd *)tmp->data;
      if (fd->callback == (void *)&handle_client &&
	  ((t_client *)fd->data)->type_cli == GUI)
	{
	  msz(serv, fd, NULL);
	  sgt(serv, fd, NULL);
	  mct(serv, fd, NULL);
	  tna(serv, fd, NULL);
	  pnw_init(serv, fd);
	  enw_init(serv, fd);
	}
      tmp = tmp->next;
    }
}

static void	replace_eggs_and_notify_gui(t_server *serv)
{
  t_list	*tmp;

  tmp = serv->game.eggs;
  while (tmp)
    {
      ((t_egg *)tmp->data)->x %= serv->game.width;
      ((t_egg *)tmp->data)->y %= serv->game.height;
      gen_food(serv);
      tmp = tmp->next;
    }
  notify_gui(serv);
}

static void	replace_players_and_notify_gui(t_server *server)
{
  t_list	*tmp;
  t_selfd	*fd;
  t_client	*client;

  tmp = server->watch;
  while (tmp)
    {
      fd = (t_selfd *)tmp->data;
      if (fd->callback == (void *)&handle_client && fd->data)
	if ((client = (t_client *)fd->data) && client->type_cli == IA)
	  {
	    client->x %= server->game.width;
	    client->y %= server->game.height;
	    gen_food(server);
	  }
      tmp = tmp->next;
    }
  gen_ressource(server, "linemate", AREA / 2 + DEMI_PERIMETER / 2, 0);
  gen_ressource(server, "deraumere", AREA / 3 + DEMI_PERIMETER / 2, 0);
  gen_ressource(server, "sibur", AREA / 4 + DEMI_PERIMETER / 2, 0);
  gen_ressource(server, "mendiane", AREA / 6 + DEMI_PERIMETER / 2, 0);
  gen_ressource(server, "phiras", AREA / 8 + DEMI_PERIMETER / 2, 0);
  gen_ressource(server, "thystame", AREA / 10 + DEMI_PERIMETER / 2, 0);
  replace_eggs_and_notify_gui(server);
}

static int	gen_new_map(t_server *server, int new_x, int new_y)
{
  int		y;
  int		x;
  t_map		**map;

  if (!(map = malloc(sizeof(t_map *) * (new_y + 1))))
    return (EXIT_FAILURE);
  y = 0;
  while (y < new_y)
    {
      x = 0;
      if (!(map[y] = malloc(sizeof(t_map) * (new_x))))
	return (EXIT_FAILURE);
      while (x < new_x)
	memset(&(map[y][x++]), 0, sizeof(t_map));
      ++y;
    }
  y = 0;
  while (y < (int)server->game.height)
    free(server->map[y++]);
  free(server->map);
  server->map = map;
  server->game.height = new_y;
  server->game.width = new_x;
  replace_players_and_notify_gui(server);
  return (EXIT_SUCCESS);
}

void	resize(t_server *server, char **args)
{
  int	x;
  int	y;

  if (!args[0] || !args[1])
    {
      printf("%susage : resize __x_size__ __y_size__\n%s", RED, WHITE);
      return ;
    }
  if ((x = atoi(args[0])) <= 0 || (y = atoi(args[1])) <= 0)
    {
      printf("%sx_size and y_size must be positive.\n%s", RED, WHITE);
      return ;
    }
  if (gen_new_map(server, x, y))
    printf("%scan not generate new map. (not enough memory)\n%s", RED, WHITE);
}
