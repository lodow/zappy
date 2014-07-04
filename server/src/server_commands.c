/*
** server_commands.c for server_commands.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu Jul  3 22:47:18 2014 Nicolas Bridoux
** Last update Fri Jul  4 10:56:25 2014 Nicolas Bridoux
*/

#include "server.h"

static t_admin	g_cmds[] =
  {
    {"servertime", &servertime},
    {"kick", &kick},
    {"add", &add},
    {"shutdown", &serv_shutdown},
    {"help", &help},
    {NULL, NULL}
  };

static void	epur_str(char *str)
{
  int		i;
  int		j;

  i = -1;
  while (str[++i])
    if (str[i] == '\t')
      str[i] = ' ';
  i = -1;
  while (str[++i])
    while (str[i] == ' ' && str[i + 1] == ' ' && (j = i))
      while (str[j])
	{
	  str[j] = str[j + 1];
	  ++j;
	}
  if (strlen(str) && str[strlen(str) - 1] == ' ')
    str[strlen(str) - 1] = '\0';
  while (str[0] == ' ' && (j = -1))
    while (str[++j])
      str[j] = str[j + 1];
}

void	exec_server_command(t_server *serv)
{
  char	**tab;
  int	i;

  epur_str(serv->cmd);
  if (!(tab = my_str_to_wordtab(serv->cmd, ' ')))
    return ;
  i = -1;
  while (g_cmds[++i].name)
    if (tab[0] && !strcmp(tab[0], g_cmds[i].name))
      {
	g_cmds[i].ptr(serv, &tab[1]);
	free_tab(tab);
	return ;
      }
  free_tab(tab);
  if (serv->cmd && strlen(serv->cmd))
    printf("%s%s : unknown command\n%s", RED, serv->cmd, WHITE);
}
