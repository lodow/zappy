#ifndef SERVER_H_INCLUDED
# define SERVER_H_INCLUDED

# include <signal.h>
# include <string.h>

# include "tab.h"
# include "network.h"
# include "select.h"

typedef struct	s_server
{
  int		quit;
  t_net		**listener;
  t_list	*watch;
}		t_server;

typedef struct	s_dumb_client
{
  t_net		*sock;
  //this struct is only used to decide if it's a ai or a gui client

//ring buffers here
}		t_dumb_client;

int	listen_on_port(t_server *serv, char *port, int socktype);
void	close_server_binds(t_server *serv);
void	serv_verbose(t_server *serv);
void	server_setup_select(t_server *serv);
void	handle_newconnection(t_selfd *fd, t_server *serv);
void	quit_server(t_server *serv);
void	log_connection(t_net *sock, char *message);

#endif /* !SERVER_H_INCLUDED */
