/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Tue Apr 29 16:50:42 2014 Nicolas Bridoux
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

  char		type_cli;
  char		*rb_r;
  size_t	len_r;

  char		*rb_w;
  size_t	len_w;
}		t_selfd;

void	do_select(t_list *fds, void *global_arg);
t_selfd	*create_fd(int fd, void *data, void (*call)());

int	read_from_client(t_selfd *fd);
void	check_command(t_selfd *fd);

#endif /* !SELECT_H_INCLUDED */
