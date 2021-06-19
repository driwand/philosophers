
CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = philo

SRCS = main.c \
	utils.c \
	parser.c \
	simulation.c

OBJS = $(SRCS:.c=.o)

HEADERS = -I .

all : $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(HEADERS) $(OBJS) -o $(NAME)

%.o : %.c philo.h 
	$(CC) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
