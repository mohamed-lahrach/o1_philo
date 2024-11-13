CC = cc
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./philo 5 800 200 200 2
# CFLAGS = -Wall -Wextra -Werror 
CFLAGS = -Wall -Wextra -Werror

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
