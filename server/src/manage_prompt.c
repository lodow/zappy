/*
** manage_prompt.c for manage_prompt.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu Jul  3 22:02:03 2014 Nicolas Bridoux
** Last update Thu Jul  3 23:08:53 2014 Nicolas Bridoux
*/

#include "server.h"

static void	handle_special_cases(t_server *serv, char *buff, char **cmd)
{
  if (!memcmp(buff, "\x3\x0\x0\x0\x0", 5))
    kill(getpid(), SIGINT);
  if (*cmd && strlen(*cmd) && !memcmp(buff, "\x7F\x0\x0\x0\x0", 5))
    {
      (*cmd)[strlen(*cmd) - 1] = '\0';
      printf("\b ");
      fflush(stdout);
    }
  if (buff[0] == 13)
    {
      exec_server_command(serv, *cmd);
      free(*cmd);
      *cmd = NULL;
      printf("%s", PROMPT);
    }
}

int		handle_prompt(t_selfd *fd, t_server *serv)
{
  static char	*cmd = NULL;
  static char	buff[10] = {0};
  int		r;

  if (!cmd)
    cmd = strdup("");
  if (ISREADABLE(fd))
    {
      if ((r = read(STDIN_FILENO, buff, sizeof(buff))) > 0)
	buff[r] = '\0';
      handle_special_cases(serv, buff, &cmd);
      if (buff[0] >= 32 && buff[0] < 127)
	cmd = concat(cmd, buff);
      if (cmd)
	printf("\r%s%s", PROMPT, cmd);
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
