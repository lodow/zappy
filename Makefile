##
## Makefile for Make in /home/moriss
##
## Made by hugues morisset
## Login   <moriss_h@epitech.net>
##
## Started on  Mon Oct 22 09:20:28 2012 hugues morisset
## Last update Mon Apr 28 16:10:38 2014 Hugues
##

NAME	=	zappy

SUBDIRS	=	server \
			ia \
			gui

RULES	=	zappy \
			client

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
