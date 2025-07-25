# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 14:17:31 by jbaetsen          #+#    #+#              #
#    Updated: 2025/07/08 12:44:25 by rmhazres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===================== #
#    	 Colors	        #
# ===================== #
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
RESET='\033[0m'

# ===================== #
#     Configuration     #
# ===================== #
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
LIBFT_FLAGS = -L./libraries -lft

# ===================== #
#      Directories      #
# ===================== #
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = includes

# ===================== #
#    	  Files	        #
# ===================== #
NAME = minishell
LIBFT = ./libraries/libft.a

# ===================== #
#        Sources        #
# ===================== #
SRC_MAIN = 		$(SRC_DIR)/main.c \

SRC_SIGNALS =	$(SRC_DIR)/signals/signals.c \
				$(SRC_DIR)/signals/heredoc_signals.c

SRC_ENV =		$(SRC_DIR)/env/env_list.c \
				$(SRC_DIR)/env/env_utils.c

SRC_EXECUTOR =  $(SRC_DIR)/executor/exec_controls.c \
				$(SRC_DIR)/executor/redirection.c \
				$(SRC_DIR)/executor/exec.c\
				$(SRC_DIR)/executor/exec_utils.c \
				$(SRC_DIR)/executor/pipe.c\
				$(SRC_DIR)/executor/heredoc.c

SRC_BUILTINS = 	$(SRC_DIR)/builtins/pwd.c \
				$(SRC_DIR)/builtins/cd.c \
				$(SRC_DIR)/builtins/echo.c \
				$(SRC_DIR)/builtins/env.c \
				$(SRC_DIR)/builtins/export.c \
				$(SRC_DIR)/builtins/unset.c \
				$(SRC_DIR)/builtins/exit.c \
				$(SRC_DIR)/builtins/run_builtin.c\

SRC_UTILS = 	$(SRC_DIR)/utils/shell_init.c \
				$(SRC_DIR)/utils/str_utils.c \
				$(SRC_DIR)/utils/str_two_utils.c \
				$(SRC_DIR)/utils/args_utils.c \
				$(SRC_DIR)/utils/memory.c \
				$(SRC_DIR)/utils/fds.c\
				$(SRC_DIR)/utils/shell_exit.c \
				$(SRC_DIR)/utils/error.c

SRC_LEXER = 	$(SRC_DIR)/lexer/lexer_utils.c \
				$(SRC_DIR)/lexer/lexer.c \
				$(SRC_DIR)/lexer/state_handling.c \
				$(SRC_DIR)/lexer/redir_state_utils.c \
				$(SRC_DIR)/lexer/token_utils.c \
				$(SRC_DIR)/lexer/env_state_utils.c \
				$(SRC_DIR)/lexer/assign.c \
				$(SRC_DIR)/lexer/validate.c \
				$(SRC_DIR)/lexer/quotes_logic.c

SRC_PARSER = 	$(SRC_DIR)/parser/parser.c \
				$(SRC_DIR)/parser/parser_utils.c \
				$(SRC_DIR)/parser/parser_redirs.c \
				$(SRC_DIR)/parser/parser_redir_utils.c \
				$(SRC_DIR)/parser/parser_init.c \
				$(SRC_DIR)/parser/parse_quotes.c

SRC = 	$(SRC_MAIN) $(SRC_SIGNALS) $(SRC_ENV) $(SRC_BUILTINS) \
		$(SRC_UTILS) $(SRC_LEXER) $(SRC_PARSER) $(SRC_EXECUTOR) \

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# ===================== #
#        Rules	        #
# ===================== #
all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_FLAGS) -lreadline
	@echo $(GREEN)"Compiled $(NAME)"$(RESET)

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