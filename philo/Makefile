CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

NAME = philo
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC)  $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
