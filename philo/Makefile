NAME = philo

SRCS = main.c helpers.c initial_state.c philo_actions.c philo_program.c time_functions.c

CC = cc -g

CFLAGS = -Wall -Werror -Wextra -pthread

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRCS) $(OBJ) philo.h
		  $(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean: 
		rm -rf $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re