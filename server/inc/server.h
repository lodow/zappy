#ifndef SERVER_H_INCLUDED
# define SERVER_H_INCLUDED

# include <signal.h>
# include <string.h>

# include "include.h"
# include "network.h"
# include "select.h"

typedef struct	s_server
{
  int		quit;
  t_net		**listener;
  t_list	*watch;
}		t_server;

int	listen_on_port(t_server *serv, char *port);

#endif /* !SERVER_H_INCLUDED */
