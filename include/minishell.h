/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:41 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/16 16:07:53 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* printf, perror */
# include <stdio.h>
/* malloc, free, exit, getenv */
# include <stdlib.h>
/* writem access, open, read, close, fork, getcwd, chdir, dup, dup2, pipe
execve, isatty, ttyname, ttyslot */
# include <unistd.h>
/* readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
add_history*/
# include <readline/readline.h>
# include <readline/history.h>
/* signal, sigaction, sigemptyset, sigaddset, kill */
# include <sys/wait.h>
/* stat, lstat, fstat */
# include <sys/stat.h>
/* open */
# include <fcntl.h>
/* opendir, readdir, closedir */
# include <dirent.h>
/* strerror */
# include <string.h>
/* ioctl */
# include <sys/ioctl.h>
/* tcsetattr, tcgetattr */
# include <termios.h>
/* tgetent, tgetflag, tgetnum, getstr, tgoto, tputs */
# include <curses.h>
# include <stdbool.h>
# include "libft.h"

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36;1m"
# define RESET   "\x1b[0m"

# define SYNTAX_ERR "minishell: syntax error near unexpected token `%s'\n"
# define NEWLINE_ERR "minishell: unexpected newline while looking for matching `%c'\n"
# define PARENTHESIS_ERR "minishell: unexpected newline while looking for closing `%c'\n"

// typedef and struct used in conjunction to create an alias for s_tree
typedef struct s_tree
{
	char			*value;
	int				operator;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;


enum e_token
{
	PIPE = '|',
	PARENTHESIS_L = '(',
	PARENTHESIS_R = ')',
	S_QUOTE = '\'',
	D_QUOTE = '\"',
	OUT = '>',
	IN = '<',
	WORD = 1000,
	AND = 1001,
	OR = 1002,
	APPEND = 1003,
	HERE_DOC = 1004,
	BUILTIN = 1005,
};

// builtins/is_builtin.c
int	is_builtins(char *str);

#endif
