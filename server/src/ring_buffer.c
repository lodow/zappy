/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Fri May 30 18:41:16 2014 Nicolas Bridoux
*/

#include "ring_buffer.h"

t_rbuf	*create_ring_buffer(ssize_t size)
{
  t_rbuf	*rbuf;

  if ((rbuf = malloc(1 * sizeof(t_rbuf))) == NULL)
    return (NULL);
  if ((rbuf->buf = malloc(sizeof(size * sizeof(char)))) == NULL)
    {
      free(rbuf);
      return (NULL);
    }
  rbuf->idx_r = 0;
  rbuf->idx_w = 0;
  rbuf->size = size;
  return (rbuf);
}

void	*destroy_ring_buffer(t_rbuf *buf)
{
  if (buf)
    {
      free(buf->buf);
      free(buf);
    }
}

ssize_t	ring_buffer_left_read(t_rbuf *buf)
{
  return (((buf->idx_w + buf->size) - buf->idx_r) % buf->size);
}

ssize_t	ring_buffer_left_write(t_rbuf *buf)
{
  return (((buf->idx_r + buf->size) - buf->idx_w) % buf->size);
}
