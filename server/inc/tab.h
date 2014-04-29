/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef INCLUDE_H_INCLUDED
# define INCLUDE_H_INCLUDED

# define _GNU_SOURCE
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

# define UNSEDP __attribute__((unused))

# define PTRT_PACK 10

int	ptr_tab_size(void **tab);
void	**add_ptr_t_tab(void **tab, void *add);
void	**concat_ptr_tab(void **tab1, void **tab2);
void	rm_ptr_f_tab(void **tab, void *ptr);
void	free_ptr_tab(void **tab, void (*f)(void *ptr));

#endif /* !INCLUDE_H_INCLUDED */
