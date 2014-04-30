/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Wed Apr 30 18:02:34 2014 Nicolas Bridoux
*/

#ifndef _LISTE_H
# define _LISTE_H

# include <stdlib.h>

typedef struct		s_list
{
  void			*data;
  struct s_list		*next;
}			t_list;

void	add_to_list(t_list **begin, void *data);
void	rm_list(t_list *begin, void (*f)(void*));
void	apply_on_list(t_list *begin, int (*f)(void*, void*), void *arg);
void	rm_from_list(t_list **begin, t_list *trm, void (*f)(void*));
int	list_size(t_list *begin);
t_list	*find_in_list(t_list *begin, void *data);

#endif /* !_LISTE_H */
