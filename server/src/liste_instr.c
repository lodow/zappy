/*
** liste_instr.c for liste_instr.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Thu May 22 09:51:05 2014 Nicolas Bridoux
** Last update Thu May 22 11:31:46 2014 Nicolas Bridoux
*/

#include "server.h"

int	sort_instr(void *a, void *b)
{
  if (!a || !b)
    return (0);
  return (((t_instr *)a)->time < ((t_instr *)b)->time);
}

void		add_to_ordered_list(t_list **list, void *data,
				    int (*sort)(void *, void *))
{
  t_list	*tmp;
  t_list	*new;

  if (!list || !(new = malloc(sizeof(t_list))))
    return ;
  new->data = data;
  new->next = NULL;
  if (!(tmp = *list) && (*list = new))
    return ;
  while (tmp->next && sort(tmp->next->data, new->data))
    tmp = tmp->next;
  if (tmp == *list && !sort(tmp->data, new->data))
    {
      new->next = tmp;
      *list = new;
      return ;
    }
  new->next = tmp->next;
  tmp->next = new;
}
