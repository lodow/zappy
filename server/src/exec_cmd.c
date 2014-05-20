/*
** exec_cmd.c for exec_cmd.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 11:54:45 2014 Nicolas Bridoux
** Last update Tue May 20 15:10:25 2014 Nicolas Bridoux
*/

#include "server.h"

static t_cmd	g_ia_cmd[] =
  {
    {"avance", 0, 7, NULL},
    {"droite", 0, 7, NULL},
    {"gauche", 0, 7, NULL},
    {"voir", 0, 7, NULL},
    {"inventaire", 0, 1, NULL},
    {"prend", 1, 7, NULL},
    {"pose", 1, 7, NULL},
    {"expulse", 0, 7, NULL},
    {"broadcast", 1, 7, NULL},
    {"incantation", 0, 300, NULL},
    {"fork", 0, 42, NULL},
    {"connect_nbr", 0, 0, NULL},
    {NULL, 0, 0, NULL}
  };

static t_cmd	g_gui_cmd[] =
  {
    {NULL, 0, 0, NULL}
  };

static int	check_gui(__attribute__((unused))t_selfd *fd,
			  __attribute__((unused))char **tab)
{
  return (-1);
}

static int	check_ia(t_selfd *fd, char **tab)
{
  int		i;
  t_list	*cmd;
  t_client	*client;

  i = -1;
  client = (t_client *)fd->data;
  while (g_ia_cmd[++i].name)
    if (tab[0] && !strcmp(g_ia_cmd[i].name, tab[0]))
      if (!g_ia_cmd[i].args || (g_ia_cmd[i].args && tab[1]))
	return (g_ia_cmd[i].delay);
  if ((cmd = dequeue(&(client->cmds))))
    {
      free(cmd->data);
      free(cmd);
    }
  send_response(fd, "ko");
  return (-1);
}

int	is_cmd_valid(t_selfd *fd, char *cmd)
{
  char	**tab;
  int	ret;

  if (!(tab = my_str_to_wordtab(cmd, ' ')))
    return (-1);
  if (((t_client *)fd->data)->type_cli == IA)
    ret = check_ia(fd, tab);
  else
    ret = check_gui(fd, tab);
  free_tab(tab);
  return (ret);
}

