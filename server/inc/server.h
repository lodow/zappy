#ifndef SERVER_H_INCLUDED
# define SERVER_H_INCLUDED

# include <signal.h>
# include <string.h>
# include <stdarg.h>

# include "tab.h"
# include "network.h"
# include "select.h"
# include "game.h"

# define RED_BOLD	"\033[1;31m"
# define GREEN_BOLD	"\033[1;32m"
# define YELLOW_BOLD	"\033[1;33m"
# define BLUE_BOLD	"\033[1;34m"
# define MAGENTA_BOLD	"\033[1;35m"
# define CYAN_BOLD	"\033[1;36m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;0m"
# define WARNING	1
# define ERROR		2
# define SENDING	3
# define RECEIVING	4

typedef struct	s_server
{
  int		quit;
  t_net		**listener;
  t_list	*watch;
  t_game	game;
}		t_server;

typedef struct	s_client
{
  t_net		*sock;
  char		type_cli;
  char		*teamname;
  // pour toutes les infos relatives à un client
}		t_client;

int	listen_on_port(t_server *serv, char *port, int socktype);
void	close_server_binds(t_server *serv);
void	serv_verbose(t_server *serv);
void	server_setup_select(t_server *serv);
void	handle_newconnection(t_selfd *fd, t_server *serv);
void	quit_server(t_server *serv);
void	log_connection(t_net *sock, char *message);

/*
** exec_cmd.c
*/

void	handle_exec_cmd(t_selfd *fd, char *cmd);

/*
** parse_command_line.c
*/

int	parse_command_line(t_server *server, int ac, char *av[]);

/*
** log.c
*/

void	server_log(char warn_level, const char *fmt, ...);
void	display_start(t_server *server);

#endif /* !SERVER_H_INCLUDED */
