/*
** server_commands.c for server_commands.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu Jul  3 22:47:18 2014 Nicolas Bridoux
** Last update Thu Jul  3 23:16:18 2014 Nicolas Bridoux
*/

#include "server.h"

// - changer time server (servertime __time__)
// - kick un player (kick __num_player__)
// - ajouter de la food (addFood __num_food__)
// - éteindre le serveur (shutdown)
// - help

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

void	exec_server_command(__attribute__((unused))t_server *serv, char *cmd)
{
  epur_str(cmd);
  printf("J'ai tapé : {%s}\n", cmd);
  // mettre la cmd dans la struct serv ?
}
