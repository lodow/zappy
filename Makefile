##
## Makefile for Make in /home/moriss
##
## Made by hugues morisset
## Login   <moriss_h@epitech.net>
##
## Started on  Mon Oct 22 09:20:28 2012 hugues morisset
## Last update Sun May  4 11:45:41 2014 fabien.linardon
##

NAME	=	zappy

SUBDIRS	=	server \
		ia \
		gui

RULES	=	zappy \
		client \
		graphic \

RM	=	rm -f

$(NAME):
	@for dir in $(SUBDIRS); do \
	echo "--- $$dir ---"; make --no-print-directory -C $$dir all; \
	done

all: $(NAME)

clean:
	@for dir in $(SUBDIRS); do \
	echo "--- $$dir ---"; make --no-print-directory -C $$dir clean; \
	done

fclean:
	$(RM) $(RULES)
	@for dir in $(SUBDIRS); do \
	echo "--- $$dir ---"; make --no-print-directory -C $$dir fclean; \
	done

re: fclean all

.PHONY:	all clean fclean re $(SUBDIRS)
