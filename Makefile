# ---------------- VARIABLES ----------------

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
HEADER = philo.h

SRCS = \
	main.c \
	exit.c \
	init.c \
	parse.c \
	monitor_routine.c \
	philo_routine.c \
	utils.c \

OBJS = $(SRCS:.c=.o)

NAME = philo

# ------------- COMPILING ----------------

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


# ------------ CLEAN RULES --------------

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

