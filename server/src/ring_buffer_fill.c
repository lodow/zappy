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

void		write_buffer(t_rbuf *buf, const char *data, size_t size)
{
  size_t	i;
  size_t	born;
  char	*buffer;

  born = buf->size;
  buffer = buf->buf;
  i = 0;
  while (i < size)
    {
      buffer[(buf->idx_w + i) % born] = data[i];
      ++i;
    }
  buf->idx_r += born;
  buf->idx_w += i;
  if (buf->idx_w >= buf->idx_r)
    buf->idx_r = buf->idx_w + 1;
  buf->idx_r %= born;
  buf->idx_w %= born;
}

size_t		read_buffer(t_rbuf *buf, char *data, size_t size)
{
  size_t	i;
  size_t	born;
  size_t	left;
  char	*buffer;

  left = ring_buffer_left_read(buf);
  born = buf->size;
  buffer = buf->buf;
  i = 0;
  size = size < left ? size : left;
  while (i < size)
    {
      data[i] = buffer[(buf->idx_r + i) % born];
      ++i;
    }
  buf->idx_r = (buf->idx_r + i) % born;
  return (size);
}

void	rollback_read_buffer(t_rbuf *buf, size_t bysize)
{
  buf->idx_r = (buf->idx_r - bysize + 2 * buf->size) % buf->size;
}
