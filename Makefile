##
## Makefile for Make in /home/moriss
##
## Made by hugues morisset
## Login   <moriss_h@epitech.net>
##
## Started on  Mon Oct 22 09:20:28 2012 hugues morisset
## Last update Sun Mar 30 16:01:40 2014 hugues morisset
##

NAME	=	zappy

SUBDIRS	=	server \
			ia \
			gui

RULES	=	server \
			gui

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
