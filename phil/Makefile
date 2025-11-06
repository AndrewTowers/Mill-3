NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -g -fsanitize=thread
SRC = main.c utils.c init.c routine.c monitor.c actions.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Compilation complete: $(NAME)"

clean:
	@rm -rf $(OBJ)
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "Executable cleaned."

re: fclean all
	@echo "Recompilation complete."

.PHONY: all clean fclean re