SRCS = \
helpfunc.c\
init.c\
threads.c\
life.c\
actions.c\
philo.c\

OBJECTS = $(SRCS:.c=.o)


CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = philo



all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

clean :
		rm -f *.o
fclean: clean
		rm -f $(NAME)
re: fclean all