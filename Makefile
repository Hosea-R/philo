CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c data.c philo.c action.c time.c utils.c
OBJS = $(SRCS:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
