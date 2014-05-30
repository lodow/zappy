/*
** my_str_to_wordtab.c for my_str_to_wordtab.c in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Tue May 20 13:50:08 2014 Nicolas Bridoux
** Last update Fri May 30 19:27:42 2014 Nicolas Bridoux
*/

#include "server.h"

static size_t	count_words(char *str, char delim)
{
  size_t	count;

  count = 1;
  while (*str++)
    if (*str == delim)
      ++count;
  return (count);
}

void	free_tab(char **tab)
{
  int	i;

  i = -1;
  while (tab && tab[++i])
    free(tab[i]);
  free(tab);
}

char		**my_str_to_wordtab(char *str, char delim)
{
  size_t	i;
  size_t	j;
  size_t	k;
  char		**ret;
  char		tmp;

  i = -1;
  k = -1;
  j = 0;
  if (!(ret = malloc(sizeof(char *) * (count_words(str, delim) + 1))))
    return (NULL);
  while (str[++i])
    if (str[i] == delim)
      {
	tmp = str[i];
	str[i] = '\0';
	if (!(ret[++k] = strdup(&str[j])))
	  return (NULL);
	str[i] = tmp;
	j = i + 1;
      }
  if (!(ret[++k] = strdup(&str[j])))
    return (NULL);
  ret[++k] = NULL;
  return (ret);
}
