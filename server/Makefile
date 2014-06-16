##
## Makefile for Makefile in /home/Epitech
##
## Made by moriss_h
## Login   <moriss_h@epitech.net>
##
## Started on  Sun Jun  9 03:35:24 2013 Hugues
## Last update Sat Jun  7 15:08:10 2014 Nicolas Bridoux
##

SRC		=	main.c \
			inet.c \
			inet_accept.c \
			inet_asynchronous_connect.c \
			liste.c \
			liste_find.c \
			liste_instr.c \
			ptr_tab.c \
			select.c \
			server_network.c \
			new_connection.c \
			remove_player.c \
			add_cmd.c \
			log.c \
			parse_command_line.c \
			check_team_names.c \
			timeout.c \
			manage_instr.c \
			clean.c \
			exec_cmd.c \
			handle_callbacks.c \
			ring_buffers.c \
			eggs.c \
			my_str_to_wordtab.c \
			gen_ressources.c \
			cmd_ia/avance.c \
			cmd_ia/droite.c \
			cmd_ia/gauche.c \
			cmd_ia/inventaire.c \
			cmd_ia/prend.c \
			cmd_ia/pose.c \
			cmd_ia/connect_nbr.c \
			cmd_ia/voir.c \
			cmd_ia/fill_square_voir.c \
			cmd_ia/ia_fork.c \
			cmd_ia/expulse.c \
			cmd_ia/incantation.c \
			cmd_ia/end_game.c \
			cmd_ia/broadcast.c \
			cmd_gui/msz.c \
			cmd_gui/bct.c \
			cmd_gui/mct.c \
			cmd_gui/tna.c \
			cmd_gui/ppo.c \
			cmd_gui/plv.c \
			cmd_gui/pin.c \
			cmd_gui/sgt.c \
			cmd_gui/sst.c \
			cmd_gui/send.c \
			cmd_gui/pnw.c \
			cmd_gui/ebo.c \
			cmd_gui/pex.c \
			cmd_gui/pbc.c \
			cmd_gui/pic.c \
			cmd_gui/pie.c \
			cmd_gui/pfk.c \
			cmd_gui/enw.c \
			cmd_gui/pdr.c \
			cmd_gui/pgt.c \
			cmd_gui/pdi.c \
			cmd_gui/eht.c \
			cmd_gui/edi.c \
			cmd_gui/seg.c \
			cmd_gui/smg.c \

CC		=	gcc
FILETYPE	=	.c

RM		=	rm -f

NAME		=	zappy

OBJDIR		=	obj/
SRCDIR		=	src/
INCDIR		=	inc/

CFLAGS		+=	-I$(INCDIR)
CFLAGS		+=	-Wall -Wextra -Winit-self
CFLAGS		+=	-Wunused-function -pipe -Winit-self -g

LDFLAGS		+=	-Wl,-O1

OBJ		=	$(patsubst %${FILETYPE},${OBJDIR}%.o, $(SRC))
DEPS		=	$(patsubst %${FILETYPE}, ${OBJDIR}%.d, $(SRC))

PRINTFLAGS	=	0

dummy		:=	$(shell test -d $(OBJDIR) || mkdir -p $(OBJDIR))
dummy		:=	$(shell test -d $(SRCDIR) || mkdir -p $(SRCDIR))
dummy		:=	$(shell test -d $(INCDIR) || mkdir -p $(INCDIR))

$(OBJDIR)%.o:		$(patsubst %${FILETYPE}, ${SRCDIR}%${FILETYPE}, %${FILETYPE})
			@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
ifneq ("$(shell tty)", "not a tty")
			@if [ $(PRINTFLAGS) = "0" ]; then \
			echo -e "Compile flags { $(CFLAGS) }" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' \
			| sed 's/[{}]/\x1B[34m&\x1B[0m/g'; fi
			$(eval PRINTFLAGS = 1)
			@echo -e "Compiling $< $(patsubst %.o, %.d, $@)" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' | sed 's/d/\x1B[35m&\x1B[0m/'
			@$(CC) $(CFLAGS) -c $< -o $@
			@$(CC) $(CFLAGS) -MM -MF $(patsubst %.o, %.d, $@) -MT $@ -MT $(patsubst %.o, %.d, $@) -c $<
else
			$(CC) $(CFLAGS) -c $< -o $@
			$(CC) $(CFLAGS) -MM -MF $(patsubst %.o, %.d, $@) -MT $@ -MT $(patsubst %.o, %.d, $@) -c $<
endif

$(NAME):	$(OBJ)
ifneq ("$(shell tty)", "not a tty")
		@echo -e "Linking $@ { $(LDFLAGS) }" | sed 's/^-e //' \
		| sed 's/[-a-zA-Z]\+/\x1B[34m&\x1B[0m/g'
		@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
		@cp -f $(NAME) ../$(NAME)
else
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
		@cp -f $(NAME) ../$(NAME)
endif

-include $(DEPS)

all:	$(NAME)

clean:
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing object !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[35m&\x1B[0m/g'
	@$(RM) $(OBJ) $(DEPS)
else
	$(RM) $(OBJ) $(DEPS)
endif

fclean:	clean
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing ${NAME} !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[36m&\x1B[0m/g'
	@$(RM) $(NAME)
else
	$(RM) $(NAME)
endif

re:	fclean all

help:
	@echo -e "\033[37mTarget available: all, ${NAME}, clean, fclean\033[00m" | sed 's/^-e //'

.PHONY:	all clean fclean re help

