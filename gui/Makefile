##
## Makefile for Makefile in /home/Epitech
##
## Made by moriss_h
## Login   <moriss_h@epitech.net>
##
## Started on  Sun Jun  9 03:35:24 2013 Hugues
## Last update Fri Jul  4 15:49:29 2014 fabien.linardon
##

SRC		=	main.cpp	\
			GameEngine.cpp	\
			Parser.cpp	\
			Model.cpp	\
			Shader.cpp	\
			Cube.cpp	\
			Camera.cpp	\
			AObject.cpp	\
			Geometry.cpp	\

CC		=	g++
FILETYPE	=	.cpp

RM		=	rm -f

NAME		=	graphic

OBJDIR		=	obj/
SRCDIR		=	src/
INCDIR		=	inc/

CXXFLAGS	+=	-I$(INCDIR) -I../libnetwork/inc/
CXXFLAGS	+=	-Wall -Wextra -W

LDFLAGS		+=	-Wl,-O1
LDFLAGS		+=	-lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS		+=	-L../libnetwork/ -lnet -lGL

OBJ		=	$(patsubst %${FILETYPE},${OBJDIR}%.o, $(SRC))

PRINTFLAGS	=	0

dummy		:=	$(shell test -d $(OBJDIR) || mkdir -p $(OBJDIR))
dummy		:=	$(shell test -d $(SRCDIR) || mkdir -p $(SRCDIR))
dummy		:=	$(shell test -d $(INCDIR) || mkdir -p $(INCDIR))

$(OBJDIR)%.o:		$(patsubst %${FILETYPE},${SRCDIR}%${FILETYPE}, %${FILETYPE})
			@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
ifneq ("$(shell tty)", "not a tty")
			@if [ $(PRINTFLAGS) = "0" ]; then \
			echo -e "Compile flags { $(CXXFLAGS) }" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' \
			| sed 's/[{}]/\x1B[34m&\x1B[0m/g'; fi
			$(eval PRINTFLAGS = 1)
			@echo -e "Compiling $<" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g'
			@$(CC) $(CXXFLAGS) -c $< -o $@
else
			$(CC) $(CXXFLAGS) -c $< -o $@
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

all:	$(NAME)

clean:
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing object !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[35m&\x1B[0m/g'
	@$(RM) $(OBJ)
else
	$(RM) $(OBJ)
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

