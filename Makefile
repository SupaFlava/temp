# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbaetsen <jbaetsen@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/05/01 14:17:31 by jbaetsen      #+#    #+#                  #
#    Updated: 2025/05/01 14:58:38 by jbaetsen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


# Colors #
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
RESET='\033[0m'

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes 
LIBFT_FLAGS = -L./libraries -lft

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = includes

# Files
NAME = minishell
LIBFT = ./libraries/libft.a

# Source files and object files
SRC = $(SRC_DIR)/main.c
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) $(LIBFT_FLAGS)
	@echo $(GREEN)"Creating $(NAME)"$(RESET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(CYAN)"Compiling $<"$(RESET)

$(LIBFT):
	@$(MAKE) -C ./libft
	@mkdir -p ./libraries
	@cp ./libft/libft.a ./libraries
	@echo $(YELLOW)"Moving libft.a to ./libraries"$(RESET)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C ./libft clean
	@echo $(RED)"Cleaning object files for minishell"$(RESET)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@rm -f ./includes/mlx.h
	@$(MAKE) -C ./libft fclean
	@echo $(RED)"Full clean complete"$(RESET)

re: fclean all

.PHONY: all clean fclean re