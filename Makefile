NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c srcs/utils/action.c srcs/utils/data.c \
          srcs/utils/dead.c srcs/utils/philosopher.c \
          srcs/utils/priority.c srcs/utils/time.c \
          srcs/utils/utils.c
	   
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re