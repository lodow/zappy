/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Fri May 30 18:41:16 2014 Nicolas Bridoux
*/

#ifndef RING_BUFFER_H_INCLUDED
# define RING_BUFFER_H_INCLUDED

# include <stdlib.h>

typedef struct	s_rbuf
{
  char		*buf;
  ssize_t		size;
  ssize_t		idx_r;
  ssize_t		idx_w;
}		t_rbuf;

t_rbuf	*create_ring_buffer(ssize_t size);
void		destroy_ring_buffer(void *buf);

ssize_t	ring_buffer_left_read(t_rbuf *buf);
ssize_t	ring_buffer_left_write(t_rbuf *buf);

void		write_buffer(t_rbuf *buf, const char *data, ssize_t size);
ssize_t		read_buffer(t_rbuf *buf, char *data, ssize_t size);
void		rollback_read_buffer(t_rbuf *buf, ssize_t bysize);

#endif /* !RING_BUFFER_H_INCLUDED */
