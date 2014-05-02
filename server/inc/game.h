/*
** game.h for game.h in /home/bridou_n/projets/zappy/server
** 
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Wed Apr 30 17:49:57 2014 Nicolas Bridoux
** Last update Wed Apr 30 18:02:47 2014 Nicolas Bridoux
*/

#ifndef GAME_H_
# define GAME_H_

# include "liste.h"

typedef struct s_game	t_game;
struct		s_game
{
  size_t	width;
  size_t	height;
  size_t	max_cli;
  size_t	time;
  t_list	*team_names;
};

#endif /* !GAME_H_ */
