##
## EPITECH PROJECT, 2018
## PSU_lemipc_2017
## File description:
## Makefile
##

NAME	= lemipc

CC	= gcc

RM	= rm -f

SRCS	= ./srcs/lemipc.c

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
