# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 16:05:42 by akdovlet          #+#    #+#              #
#    Updated: 2024/05/18 22:56:46 by akdovlet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCDIR	:=	src
SRC		:=	ak_countword.c			\
			ft_free_array.c			\
			ft_ischarset.c			\
			ft_multi_split.c		\
			ft_strndup.c			\
			ft_atoi.c				\
			ft_atol.c				\
			ft_isascii.c			\
			ft_isalnum.c			\
			ft_isalpha.c			\
			ft_isdigit.c			\
			ft_isprint.c			\
			ft_isspace.c			\
			ft_split.c				\
			ft_strjoin.c			\
			ft_strdup.c				\
			ft_strlcpy.c			\
			ft_strlcat.c			\
			ft_strlen.c				\
			ft_strnstr.c			\
			ft_tolower.c			\
			ft_toupper.c			\
			ft_itoa.c				\
			ft_memcmp.c				\
			ft_memcpy.c				\
			ft_putstr_fd.c			\
			ft_putchar_fd.c			\
			ft_putnbr_fd.c			\
			ft_calloc.c				\
			ft_putendl_fd.c			\
			ft_strcmp.c				\
			ft_strncmp.c			\
			ft_bzero.c				\
			ft_free.c				\
			ft_strchr.c				\
			ft_strrchr.c			\
			ft_memmove.c 			\
			ft_memset.c 			\
			ft_memchr.c 			\
			ft_substr.c 			\
			ft_strmapi.c 			\
			ft_striteri.c 			\
			ft_strtrim.c			\
			ft_lstnew_bonus.c		\
			ft_lstadd_front_bonus.c	\
			ft_lstsize_bonus.c		\
			ft_lstlast_bonus.c		\
			ft_lstadd_back_bonus.c	\
			ft_lstdelone_bonus.c	\
			ft_lstclear_bonus.c		\
			ft_lstiter_bonus.c		\
			ft_lstmap_bonus.c		\
			get_next_line.c			\
			get_next_line_utils.c	\
			get_next_line_multi.c	\
			printf_c_handler.c		\
			printf_d_handler.c		\
			printf_dprint.c			\
			printf_ft_draft.c		\
			printf_ft_int.c			\
			printf_ft_printf.c		\
			printf_pad_manager.c	\
			printf_parsing.c		\
			printf_p_handler.c		\
			printf_s_handler.c		\
			printf_u_handler.c		\
			printf_x_handler.c
SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))
OBJDIR	:= .build
OBJ		:=	$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
DEPS	:=	$(OBJ:.o=.d)

CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -MMD -MP -Iinclude

all: create_dirs $(NAME)

create_dirs: $(OBJDIR)

$(OBJDIR):
	@if [ ! -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		@$(CC) $(CFLAGS) -c $< -o $@;
		@printf "\033[0;32%sm\tCompiled: $<\033[0m\r";

clean:
	@if [ -d "$(OBJDIR)" ]; then $(RM) -rf $(OBJDIR) && echo "\033[1;31m\tDeleted: libft $(OBJDIR)\033[0m"; fi

fclean: clean
	@if [ -f "$(NAME)" ]; then $(RM) -rf $(NAME)  && echo "\033[1;31m\tDeleted: $(NAME)\033[0m"; fi

re: fclean all


-include $(DEPS)

.PHONY: all clean fclean re create_dirs title
