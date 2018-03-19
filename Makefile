##
## EPITECH PROJECT, 2018
## PSU_lemipc_2017
## File description:
## Makefile
##

NAME	= lemipc

CC	= gcc -g3

RM	= rm -f

SRCS	= ./srcs/add_remove_player.c	\
	  ./srcs/basics.c		\
	  ./srcs/host.c			\
	  ./srcs/lemipc.c		\
	  ./srcs/manage_map.c		\
	  ./srcs/player.c		\
	  ./srcs/semaphore_basics.c	\
	  ./srcs/ia.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./includes/
CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
