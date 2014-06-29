/*
** exec_cmd.c for exec_cmd.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 11:54:45 2014 Nicolas Bridoux
** Last update Wed Jun 18 15:17:15 2014 Nicolas Bridoux
*/

#include "server.h"

static t_cmd	g_ia_cmd[] =
  {
    {"avance", 0, 7, &avance},
    {"droite", 0, 7, &droite},
    {"gauche", 0, 7, &gauche},
    {"voir", 0, 7, &voir},
    {"inventaire", 0, 1, &inventaire},
    {"prend", 1, 7, &prend},
    {"pose", 1, 7, &pose},
    {"expulse", 0, 7, &expulse},
    {"broadcast", 1, 7, &broadcast},
    {"incantation", 0, 300, &incantation},
    {"fork", 0, 42, &ia_fork},
    {"connect_nbr", 0, 0, &connect_nbr},
    {NULL, 0, 0, NULL}
  };

static t_cmd	g_gui_cmd[] =
  {
    {"msz", 0, 0, &msz},
    {"bct", 2, 0, &bct},
    {"mct", 0, 0, &mct},
    {"tna", 0, 0, &tna},
    {"ppo", 1, 0, &ppo},
    {"plv", 1, 0, &plv},
    {"pin", 1, 0, &pin},
    {"sgt", 0, 0, &sgt},
    {"sst", 1, 0, &sst},
    {NULL, 0, 0, NULL}
  };

static int	check_gui(t_selfd *fd, char **tab)
{
  int		i;

  i = -1;
  while (g_gui_cmd[++i].name)
    {
      if (tab[0] && !strcmp(g_gui_cmd[i].name, tab[0]))
	if (!g_gui_cmd[i].args || (g_gui_cmd[i].args == 1 && tab[1]) ||
	    (g_gui_cmd[i].args == 2 && tab[1] && tab[2]))
	  return (g_gui_cmd[i].delay);
    }
  send_response(fd, "suc");
  return (-1);
}

static int	check_ia(t_server *serv, t_selfd *fd, char **tab)
{
  int		i;

  i = -1;
  while (g_ia_cmd[++i].name)
    if (tab[0] && !strcmp(g_ia_cmd[i].name, tab[0]))
      if (!g_ia_cmd[i].args || (g_ia_cmd[i].args && tab[1]))
	if (strcmp(tab[0], "incantation") || check_incant(serv, fd, OK))
	  {
	    if (!strcmp(tab[0], "fork"))
	      pfk(serv, fd);
	    return (g_ia_cmd[i].delay);
	  }
  send_response(fd, "ko");
  return (-1);
}

int	is_cmd_valid(t_server *serv, t_selfd *fd, char *cmd)
{
  char	**tab;
  int	ret;

  if (!(tab = my_str_to_wordtab(cmd, ' ')))
    return (-1);
  if (((t_client *)fd->data)->type_cli == IA)
    ret = check_ia(serv, fd, tab);
  else
    ret = check_gui(fd, tab);
  if (ret < 0)
    free(cmd);
  free_tab(tab);
  return (ret);
}

void	exec_cmd(t_server *serv, t_selfd *fd, char *cmd)
{
  char	**tab;
  t_cmd	*cmd_tab;
  int	i;

  i = -1;
  if (!(tab = my_str_to_wordtab(cmd, ' ')))
    return ;
  cmd_tab = (((t_client *)fd->data)->type_cli == IA) ?
    (g_ia_cmd) : (g_gui_cmd);
  while (cmd_tab[++i].name)
    {
      if (tab[0] && !strcmp(cmd_tab[i].name, tab[0]))
	cmd_tab[i].ptr(serv, fd,
		       !strcmp(tab[0], "broadcast") ? &cmd : &tab[1]);
    }
  if (serv->instr)
    free(cmd);
  free_tab(tab);
}
