/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:41 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/23 21:17:17 by akdovlet         ###   ########.fr       */
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

typedef	enum	e_node
{
	PIPELINE,
	OPERATOR
}	t_node;

typedef enum	e_token
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
} t_type;

typedef	struct s_token
{
	int		type;
	char	*value;
	struct	s_token	*next;
}	t_token;

typedef struct s_in
{
	t_type		type;
	char		*file;
	struct s_in	*next;
}	t_in;

typedef struct s_out
{
	t_type			type;
	char			*file;
	struct s_out	*next;
}	t_out;

typedef	struct s_cmdlist
{
	char				**cmd;
	int					exit_status;
	t_in				*in;
	t_out				*out;
	struct s_cmdlist	*next;
}	t_cmdlist;


typedef struct s_ast
{
	t_node type;	
	union
	{
		struct
		{
			t_cmdlist	*lst;
			char		*cmd;
		};
		struct
		{
			t_type			value;
			struct s_ast	*left;
			struct s_ast	*right;
		};
	};
}	t_ast;


#endif
