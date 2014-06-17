/*
** server.h for server.h in /home/bridou_n/projets/zappy/server
**
** Made by Nicolas Bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue May 20 18:21:33 2014 Nicolas Bridoux
** Last update Wed Jun 18 12:10:57 2014 Nicolas Bridoux
*/

#ifndef SERVER_H_INCLUDED
# define SERVER_H_INCLUDED

# include <signal.h>
# include <string.h>
# include <stdarg.h>
# include <time.h>
# include <sys/time.h>

# include "tab.h"
# include "network.h"
# include "select.h"
# include "game.h"

# define RED_BOLD	"\033[1;31m"
# define GREEN_BOLD	"\033[1;32m"
# define YELLOW_BOLD	"\033[1;33m"
# define BLUE_BOLD	"\033[1;34m"
# define MAGENTA_BOLD	"\033[1;35m"
# define CYAN_BOLD	"\033[1;36m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;0m"
# define WARNING	1
# define ERROR		2
# define SENDING	3
# define RECEIVING	4
# define NOT_ALLOWED	1
# define NOT_KNOWN	2
# define USEC(x)	(1000000 * (x))

# define UNKNOWN	0
# define IA		1
# define GUI		2
# define BUFF_SIZE	4096

typedef struct timeval t_tv;

typedef struct	s_server
{
  int		quit;
  t_net		**listener;
  t_list	*watch;
  t_game	game;
  t_map		**map;
  t_list	*instr;
}		t_server;

typedef struct	s_cmd
{
  const char	*name;
  char		args;
  int		delay;
  void		(*ptr)(t_server *serv, t_selfd *fd, char **arg);
}		t_cmd;

typedef struct	s_instr
{
  char		*cmd;
  suseconds_t	time;
  t_selfd	*fd;
}		t_instr;

int	listen_on_port(t_server *serv, char *port, int socktype);
void	close_server_binds(t_server *serv);
void	serv_verbose(t_server *serv);
void	server_setup_select(t_server *serv);
void	log_connection(t_net *sock, char *message);
int	destroy_connection(t_server *serv, t_selfd *fd);

int	handle_newconnection(t_selfd *fd, t_server *serv);
int	handle_client(t_selfd *fd, t_server *serv);

/*
** add_cmd.c
*/

void	handle_add_cmd(t_server *server, t_selfd *fd, char *cmd);

/*
** parse_command_line.c
*/

int	parse_command_line(t_server *server, int ac, char *av[]);

/*
** check_team_names.c
*/

int	check_team_names(t_list *list, char *progname, t_server *serv);

/*
** log.c
*/

void	server_log(char warn_level, const char *fmt, ...);
int	handle_start(t_server *server);
void	add_food(t_server *serv);

/*
** timeout.c
*/

void	display_serv_queue(t_server *serv);
void	set_timeout(t_server *serv, t_selfd *fd, char *cmd, suseconds_t time);
int	get_timeout(t_server *ser, struct timeval *tv);

/*
** liste_instr.c
*/

void	add_to_ordered_list(t_list **list, void *data,
			    int (*sort)(void *, void *));
int	sort_instr(void *a, void *b);

/*
** manage_instr.c
*/

void	exec_instruction(t_server *serv);
void	push_instruction(t_server *serv, t_selfd *fd);

/*
** handle_callbacks.c
*/

void	handle_callbacks(t_server *serv, t_selfd *fd,
			 fd_set *setr, fd_set *stw);

/*
** eggs.c
*/

void	handle_eggs(t_server *serv, char *cmd);
t_egg	*find_egg(t_list *list, int num_egg, char state, char *teamname);
void	replace_egg_by_ia(t_server *serv, t_selfd *fd, t_egg *egg);

/*
** clean.c
*/

void	clean_client(t_server *serv, t_selfd *fd);
void	quit_server(t_server *serv);
void	free_instr(t_server *serv);

/*
** exec_cmd.c
*/

int	is_cmd_valid(t_server *serv, t_selfd *fd, char *cmd);
void	exec_cmd(t_server *serv, t_selfd *fd, char *cmd);

/*
** my_str_to_wordtab.c
*/

void	free_tab(char **tab);
char	**my_str_to_wordtab(char *str, char delim);

/*
** gen_ressources.c
*/

void	gen_food(t_server *serv);
void	gen_single_food(t_server *serv, char *ressource);
void	gen_rocks(t_server *serv, t_map *need);

/*
** functions for ia client in "cmd_ia" directory
*/

void	avance(t_server *serv, t_selfd *fd, char **args);
void	droite(t_server *serv, t_selfd *fd, char **args);
void	gauche(t_server *serv, t_selfd *fd, char **args);
void	voir(t_server *serv, t_selfd *fd, char **args);
char	*add_square_voir(t_server *serv, int x, int y, char *saw);
char	*concat(char *begin, char *to_add);
void	inventaire(t_server *serv, t_selfd *fd, char **args);
void	prend(t_server *serv, t_selfd *fd, char **args);
void	pose(t_server *serv, t_selfd *fd, char **args);
void	expulse(t_server *serv, t_selfd *fd, char **args);
void	broadcast(t_server *serv, t_selfd *fd, char **args);
int	check_incant(t_server *serv, t_selfd *fd, char send);
void	incantation(t_server *serv, t_selfd *fd, char **args);
void	check_end_game(t_server *serv);
size_t	nb_players_at(t_server *serv, size_t x, size_t y, int lvl);
void	ia_fork(t_server *serv, t_selfd *fd, char **args);
void	connect_nbr(t_server *serv, t_selfd *fd, char **args);

/*
** functions for gui client in "cmd_gui" directory
*/

void	msz(t_server *serv, t_selfd *fd, char **args);
void	bct(t_server *serv, t_selfd *fd, char **args);
void	mct(t_server *serv, t_selfd *fd, char **args);
void	tna(t_server *serv, t_selfd *fd, char **args);
void	ppo(t_server *serv, t_selfd *fd, char **args);
void	plv(t_server *serv, t_selfd *fd, char **args);
void	pin(t_server *serv, t_selfd *fd, char **args);
void	sgt(t_server *serv, t_selfd *fd, char **args);
void	sst(t_server *serv, t_selfd *fd, char **args);

/*
** functions for event handling for gui client
*/

void	send_to_every_gui(t_server *serv, char *msg);
void	mct_event(t_server *serv);
void	bct_event(t_server *serv, t_map *map, size_t x, size_t y);
void	pnw(t_server *serv, t_selfd *fd);
void	pnw_init(t_server *serv, t_selfd *fd);
void	ppo_event(t_server *serv, t_selfd *fd);
int	conv_orient(char orientation);
void	pex(t_server *serv, t_selfd *fd);
void	pbc(t_server *serv, t_selfd *fd, char *msg);
void	pic(t_server *serv, t_selfd *fd);
void	pie(t_server *serv, t_selfd *fd, char result);
void	plv_event(t_server *serv, size_t x, size_t y);
void	pfk(t_server *serv, t_selfd *fd);
void	enw(t_server *serv, size_t num_egg, t_selfd *fd);
void	enw_init(t_server *serv, t_selfd *fd);
void	pdr(t_server *serv, t_selfd *fd, int ressource_num);
void	pgt(t_server *serv, t_selfd *fd, int ressource_num);
void	pdi(t_server *serv, size_t fd);
void	eht(t_server *serv, size_t num_egg);
void	ebo(t_server *serv, size_t num_egg);
void	edi(t_server *serv, size_t num_egg);
void	seg(t_server *serv, char *win);
void	smg(t_server *serv, char *win);

#endif /* !SERVER_H_INCLUDED */
