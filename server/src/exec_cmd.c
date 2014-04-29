/*
** exec_cmd.c for exec_cmd.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue Apr 29 21:13:41 2014 Nicolas Bridoux
** Last update Tue Apr 29 22:15:15 2014 Nicolas Bridoux
*/

#include "server.h"

void		handle_exec_cmd(t_selfd *fd, char *cmd)
{
  t_client	*client;

  client = (t_client *)fd->data;
  if (client->type_cli == UNKNOWN)
    {
      printf("setting type of client : %s\n", !strcmp(cmd, "GRAPHIC") ? "GUI" : "IA");
      if (!strcmp(cmd, "GRAPHIC"))
	client->type_cli = GUI;
      else
	{
	  client->type_cli = IA;
	  client->teamname = strdup(cmd);
	}
    }
  else if (client->type_cli == IA)
    {
      printf("commande IA {%s} reçue\n", cmd);
      send_response(fd, "bla bla salut\n");
      send_response(fd, "une réponse de test pour tester vraiment les ring buff\n");
    }
  else if (client->type_cli == GUI)
    {
      printf("commande GUI {%s} reçue\n", cmd);
    }
}
