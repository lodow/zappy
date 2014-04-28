/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Thu Dec 13 13:14:01 2012 Hugues
*/

#include "liste.h"

int	list_size(t_list *begin)
{
  int	i;

  i = 0;
  while (begin != NULL)
    {
      begin = begin->next;
      i = i + 1;
    }
  return (i);
}

void	rm_from_list(t_list **begin, t_list *trm, void (*f)(void*))
{
  if (begin)
    while ((*begin))
      {
        if ((*begin) == trm)
          {
            (*begin) = (*begin)->next;
            if (f)
              f(trm->data);
            free(trm);
            return ;
          }
        begin = &((*begin)->next);
      }
}

void		apply_on_list(t_list *begin,
                      int (*f)(void*, void*), void *arg)
{
  t_list	*list;

  list = begin;
  while (list != NULL)
    {
      (*f)(list->data, arg);
      list = list->next;
    }
}

void	rm_list(t_list *begin, void (*f)(void*))
{
  if (begin != NULL)
    {
      if (begin->next != NULL)
        rm_list(begin->next, f);
      (*f)(begin->data);
      free(begin);
    }
}

void		add_to_list(t_list **begin, void *data)
{
  t_list	*tmp;

  if (*begin == NULL)
    {
      if ((*begin = malloc(1 * sizeof(t_list))) == NULL)
        return ;
      (*begin)->data = data;
      (*begin)->next = NULL;
      return ;
    }
  tmp = *begin;
  while ((tmp)->next != NULL)
    tmp = (tmp)->next;
  (tmp)->next = malloc(1 * sizeof(t_list));
  if ((tmp)->next != NULL)
    {
      (tmp)->next->data = data;
      (tmp)->next->next = NULL;
    }
}
