/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Jun 23 23:18:33 2014 Nicolas Bridoux
*/

#include "ring_buffer.h"

t_rbuf		*create_ring_buffer(size_t size)
{
  t_rbuf	*rbuf;

  if ((rbuf = malloc(1 * sizeof(t_rbuf))) == NULL)
    return (NULL);
  if ((rbuf->buf = malloc(size * sizeof(char))) == NULL)
    {
      free(rbuf);
      return (NULL);
    }
  rbuf->idx_r = 0;
  rbuf->idx_w = 0;
  rbuf->size = size;
  return (rbuf);
}

void		destroy_ring_buffer(void *ptr)
{
  t_rbuf	*buf;

  buf = (t_rbuf*)ptr;
  if (buf)
    {
      free(buf->buf);
      free(buf);
    }
}

void		extend_ring_buffer(t_rbuf *buf, size_t addsize)
{
  size_t	fsize;
  char		*tmp;

  fsize = buf->size + addsize;
  if (!(tmp = realloc(buf->buf, fsize)))
    return ;
  buf->buf = tmp;
  if (buf->idx_r > buf->idx_w)
    {
      addsize = ring_buffer_left_read(buf);
      if (!(tmp = malloc(addsize)))
        return ;
      addsize = read_buffer(buf, tmp, addsize);
      buf->size = fsize;
      buf->idx_r = buf->size;
      buf->idx_w = 0;
      write_buffer(buf, tmp, addsize);
      buf->idx_r = 0;
      free(tmp);
    }
  buf->size = fsize;
}

inline size_t	ring_buffer_left_read(t_rbuf *buf)
{
  return (((buf->idx_w + buf->size) - buf->idx_r) % buf->size);
}

inline size_t	ring_buffer_left_write(t_rbuf *buf)
{
  return (((buf->idx_r + buf->size - 1) - buf->idx_w) % buf->size);
}
