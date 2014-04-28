#ifndef SERVER_H_INCLUDED
# define SERVER_H_INCLUDED

# include <signal.h>
# include <string.h>

# include "include.h"
# include "network.h"
# include "select.h"

typedef struct	s_server
{
  t_list	*watch;
}		t_server;

#endif /* !SERVER_H_INCLUDED */
