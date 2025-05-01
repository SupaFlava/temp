# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: w0ffel <w0ffel@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2024/11/15 15:06:19 by w0ffel        #+#    #+#                  #
#    Updated: 2025/03/12 19:59:22 by jbaetsen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


# colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
RESET='\033[0m'

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I.
OBJ_DIR = obj/
SRC_DIR = ./src


SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_lstadd_back.c ft_lstadd_front.c \
	ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
	get_next_line.c get_next_line_utils.c ft_printf.c ft_print_utils.c ft_print_ptr.c ft_print_hex.c \
	ft_print_unsigned.c

OBJECTS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

NAME = libft.a


all:$(NAME)

$(NAME): $(OBJECTS)
	@ar rcs $@ $^
	@echo "$(GREEN)Compiled $@ $(RESET)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(MAGENTA)Compiled $< $(RESET)"


$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -f $(OBJECTS)
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Removed object files for $(NAME) $(RESET)"


fclean:clean
	@rm -f $(NAME)
	@echo "$(RED)Removed $(NAME) $(RESET)"


re:fclean $(NAME)


.PHONY: all clean fclean re
