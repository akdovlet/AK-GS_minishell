/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:41 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/20 14:47:59 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* printf, perror */
# include <stdio.h>
/* malloc, free, exit, getenv */
# include <stdlib.h>
/* write, access, open, read, close, fork, getcwd, chdir, dup, dup2, pipe
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
// lib for signals
# include "signal_minishell.h"

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36;1m"
# define RESET   "\x1b[0m"

# define HARDPATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define SYNTAX_ERR "minishell: syntax error near unexpected token `%s'\n"
# define NEWLINE_ERR "minishell: unexpected newline while looking for matching `%c'\n"
# define PARENTHESIS_ERR "minishell: unexpected newline while looking for closing `%c'\n"

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*both;
	struct	s_env	*next;
}	t_env;

typedef	enum	e_node
{
	CMD,
	OPERATOR,
	REDIR,
	PIPE_NODE,
	SUBSHELL
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
} t_type;

typedef	struct s_token
{
	int		type;
	char	*value;
	struct	s_token	*next;
}	t_token;

typedef	struct s_cmdlist
{
	t_type	type;
	char	*str;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef	struct	s_pidlst
{
	pid_t			pid;
	struct s_pidlst	*next;
}	t_pidlst;

typedef struct s_data
{
	int			read;
	int			write;
	int			status;
	int			messenger;
	bool		pipeline;
	t_pidlst	*pidlst;
	t_env		*env;
}	t_data;

typedef struct s_ast
{
	t_node type;
	union
	{
		struct
		{
			char			**cmd;
		};
		struct
		{
			t_type			op_type;
			struct s_ast	*op_left;
			struct s_ast	*op_right;
		};
		struct
		{
			t_type			redir_type;
			char			*redir_filename;
			struct	s_ast	*redir_next;
		};
		struct
		{
			struct s_ast	*pipe_left;
			struct s_ast	*pipe_right;
		};
		struct
		{
			struct s_ast	*subshell_next;
		};
	};
}	t_ast;

#endif
