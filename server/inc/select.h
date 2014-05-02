/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Tue Apr 29 21:26:14 2014 Nicolas Bridoux
*/

#ifndef SELECT_H_INCLUDED
# define SELECT_H_INCLUDED

# include <stdlib.h>
# include <stdio.h>
# include <sys/select.h>
# include <fcntl.h>
# include <errno.h>

# include "liste.h"

# define FDREAD		1
# define FDWRITE	2
# define ISREADABLE(x)	(((x)->etype & FDREAD) == FDREAD)
# define ISWRITEABLE(x)	(((x)->etype & FDWRITE) == FDWRITE)
# define CHECKREAD(x)	((x)->checktype |= FDREAD)
# define CHECKWRITE(x)	((x)->checktype |= FDWRITE)
# define UNKNOWN	0
# define IA		1
# define GUI		2
# define READ_SIZE	5
# define EOT_CHAR	'\n'

typedef struct	s_selfd
{
  int		fd;
  int		etype;
  int		checktype;
  void		*data;
  void		(*callback)(struct s_selfd *this, void *data);

  char		*rb_r;
  size_t	len_r;

  char		*rb_w;
  size_t	len_w;
}		t_selfd;

void	do_select(t_list *fds, void *global_arg);
t_selfd	*create_fd(int fd, void *data, void (*call)());

/*
** ring_buffers.c
*/

int	read_from_client(t_selfd *fd);
int	write_to_client(t_selfd *fd);
char	*get_command(t_selfd *fd);
void	send_response(t_selfd *fd, char *to_send);

#endif /* !SELECT_H_INCLUDED */
