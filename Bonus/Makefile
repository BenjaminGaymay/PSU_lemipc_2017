NAME	= lemipc

CC	= gcc -lSDLmain -lSDL -lGL -lGLU

RM	= rm -f

SRCS	= ./srcs/graphics.c \
	  ./srcs/add_remove_player.c \
	  ./srcs/ai.c \
	  ./srcs/basics.c \
	  ./srcs/host.c \
	  ./srcs/lemipc.c \
	  ./srcs/manage_map.c \
	  ./srcs/player.c \
	  ./srcs/semaphore_basics.c \
	  ./srcs/strategy.c

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
