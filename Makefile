# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 11:38:49 by akdovlet          #+#    #+#              #
#    Updated: 2024/06/19 18:51:29 by gschwand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:=	minishell
LIBFT	:= 	libft/libft.a

SRC		:=	main.c init_tree.c

SRC_DIR	:=	src
BUILD	:=	.build
SRC 	:=	$(addprefix $(SRC_DIR)/, $(SRC))
OBJ 	:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRC))
DEPS 	:=	$(OBJ:.o=.d)

CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -MMD -MP -Iinclude -Ilibft/include -g

all: create_dirs $(NAME)

create_dirs: $(BUILD)

$(BUILD):
	@if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1;32%sm\tCompiled: $<\033[0m\n";

$(LIBFT):
	@$(MAKE) --no-print-directory -C  libft

clean:
	@if [ -d $(BUILD) ]; then $(RM) -rf $(BUILD) && echo "\033[1;31m\tDeleted: $(NAME) $(BUILD)\033[0m"; fi
	@$(MAKE) --no-print-directory clean -C libft

fclean: clean
	@if [ -f $(NAME) ]; then $(RM) -rf $(NAME) && echo "\033[1;31m\tDeleted: $(NAME)\033[0m"; fi
	@$(MAKE) --no-print-directory fclean -C libft

re: fclean all

-include $(DEPS)

.PHONY: all create_dirs clean fclean re
