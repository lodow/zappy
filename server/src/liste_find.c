/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon May 19 21:51:00 2014 Nicolas Bridoux
*/

#include "liste.h"

t_list		*find_in_list(t_list *begin, void *data)
{
  t_list	*list;

  list = begin;
  while (list != NULL)
    {
      if (list->data == data)
        return (list);
      list = list->next;
    }
  return (NULL);
}

int		enqueue(t_list **begin, void *data)
{
  t_list	*new;

  if (!begin || !(new = malloc(sizeof(t_list))))
    return (EXIT_FAILURE);
  new->data = data;
  new->next = *begin;
  *begin = new;
  return (EXIT_SUCCESS);
}

t_list		*dequeue(t_list **begin)
{
  t_list	*tmp;
  t_list	*prev;

  if (!begin || !(*begin))
    return (NULL);
  prev = NULL;
  tmp = *begin;
  while (tmp->next)
    {
      prev = tmp;
      tmp = tmp->next;
    }
  if (prev)
    prev->next = NULL;
  else
    *begin = NULL;
  return (tmp);
}

t_list		*top(t_list *begin)
{
  if (!begin)
    return (NULL);
  while (begin->next)
    begin = begin->next;
  return (begin);
}
