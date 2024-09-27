NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

SRCS = action.c \
       data.c \
       dead.c \
       main.c \
       philosopher.c \
       priority.c \
       time.c \
       utils.c 
	   
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
