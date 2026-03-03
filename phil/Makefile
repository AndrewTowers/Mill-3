NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -g -fsanitize=thread
SRC = main.c utils.c init.c routine.c monitor.c actions.c
OBJ_DIR = objs
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Compilation complete: $(NAME)"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ)
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "Executable cleaned."

re: fclean all
	@echo "Recompilation complete."

.PHONY: all clean fclean re