/*
** manage_prompt.c for manage_prompt.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu Jul  3 22:02:03 2014 Nicolas Bridoux
** Last update Fri Jul  4 09:56:37 2014 Nicolas Bridoux
*/

#include "server.h"

static void	handle_special_cases(t_server *serv, char *buff)
{
  if (!memcmp(buff, "\x3\x0\x0\x0\x0", 5))
    kill(getpid(), SIGINT);
  if (serv->cmd && strlen(serv->cmd) && !memcmp(buff, "\x7F\x0\x0\x0\x0", 5))
    {
      serv->cmd[strlen(serv->cmd) - 1] = '\0';
      printf("\b ");
      fflush(stdout);
    }
  if (buff[0] == 13)
    {
      printf("\n");
      exec_server_command(serv);
      free(serv->cmd);
      serv->cmd = NULL;
      printf("%s", PROMPT);
    }
}

int		handle_prompt(t_selfd *fd, t_server *serv)
{
  static char	buff[10] = {0};
  int		r;

  if (!serv->cmd)
    serv->cmd = strdup("");
  if (ISREADABLE(fd))
    {
      if ((r = read(STDIN_FILENO, buff, sizeof(buff))) > 0)
	buff[r] = '\0';
      handle_special_cases(serv, buff);
      if (buff[0] >= 32 && buff[0] < 127)
	serv->cmd = concat(serv->cmd, buff);
      if (serv->cmd)
	printf("\r%s%s", PROMPT, serv->cmd);
      fflush(stdout);
      memset(buff, 0, sizeof(buff));
    }
  CHECKREAD(fd);
  return (0);
}

int		raw_mode(char flag)
{
  static t_term	old;
  static t_term	new;

  if (flag == ON)
    {
      if (tcgetattr(STDIN_FILENO, &old) == -1)
	return (-1);
      new = old;
      new.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
			      | INLCR | IGNCR | ICRNL | IXON);
      new.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
      new.c_cflag &= ~(CSIZE | PARENB);
      new.c_cflag |= CS8;
      if (tcsetattr(STDIN_FILENO, TCSANOW, &new) == -1)
	return (-1);
    }
  else
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) == -1)
      return (-1);
  return (0);
}
