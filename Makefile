# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 11:38:49 by akdovlet          #+#    #+#              #
#    Updated: 2024/09/19 14:44:16 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:=	minishell
LIBFT	:= 	libft/libft.a

SRC		:=	main.c							\
			AST/AST_allocations.c			\
			AST/AST_debugging.c				\
			AST/AST_redir_nodes.c			\
			AST/AST_redir_utils.c			\
			AST/AST_utils.c					\
			AST/AST_wait_nodes.c			\
			AST/AST.c						\
			AST/cmd_list.c					\
			AST/split_cmdlst.c				\
			env/env_cpy.c					\
			env/env_lst_utils.c				\
			env/env_setup.c					\
			env/env_utils.c					\
			setup/setup_shell.c				\
			setup/setup_signal.c			\
			token/debugging.c				\
			token/definitions.c				\
			token/definitions2.c			\
			token/grammar_check.c			\
			token/parenthesis.c				\
			token/syntax_error.c			\
			token/syntax_input.c			\
			token/syntax_order.c			\
			token/token_lst_utils.c			\
			token/tokenize.c				\
			token/type_manager.c			\
			token/word_manager.c			\
			builtins/cd.c					\
			builtins/pwd.c					\
			builtins/echo.c					\
			builtins/export.c				\
			builtins/export2.c				\
			builtins/unset.c				\
			builtins/env.c					\
			builtins/exit.c					\
			expand/expand.c					\
			expand/expand_split.c			\
			expand/expand_debugg.c			\
			expand/expand_quotes_utils.c	\
			expand/expand_var.c				\
			expand/lst_file_utils.c			\
			expand/sort_files.c 			\
			expand/wildcard.c				\
			exec/exec_bin.c 				\
			exec/exec_cmd.c 				\
			exec/exec_pipe.c 				\
			exec/exec.c 					\
			exec/operator.c 				\
			exec/pidlst.c 					\
			exec/subshell.c 				\
			exec/redir_lst_clear.c			\
			exec/redir_lst.c				\
			exec/redir.c					\
			exec/path_utils.c 				\
			exec/wait_pid.c					\
			exec_loop/execution_loop.c

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
	@$(CC) $(CFLAGS) -L/usr/local/lib -I/usr/local/include $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[1;32%sm\tCompiled: $<\033[0m\n";

$(LIBFT):
	@$(MAKE) --no-print-directory -C libft

clean:
	@if [ -d $(BUILD) ]; then $(RM) -rf $(BUILD) && echo "\033[1;31m\tDeleted: $(NAME) $(BUILD)\033[0m"; fi
	@$(MAKE) --no-print-directory clean -C libft

fclean: clean
	@if [ -f $(NAME) ]; then $(RM) -rf $(NAME) && echo "\033[1;31m\tDeleted: $(NAME)\033[0m"; fi
	@$(MAKE) --no-print-directory fclean -C libft

val : all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./${NAME}

re: fclean all

-include $(DEPS)

.PHONY: all create_dirs clean fclean re
