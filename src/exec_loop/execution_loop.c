/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:31:58 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/28 23:22:34 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "AST.h"
#include "exec.h"

void	process_input(t_data *data, char *line)
{
	t_token	*tk;
	int		err;

	tk = NULL;
	err = tokenize(line, &tk, data);
	if (err)
		data->status = err;
	free(line);
	data->ast_root = parse(&tk);
	token_clear(&tk);
	if (data->ast_root)
		data->status = exec_recursion(data->ast_root, data);
	ast_free(data->ast_root);
	fdlst_clear_leftovers(&data->fdlst);
}

void	interactive_shell(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline(CYAN"minishell$> "RESET);
		if (g_state == SIGINT)
		{
			data->status = 130;
			g_state = 0;
		}
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, "exit\n");
			break ;
		}
		if (line)
			add_history(line);
		process_input(data, line);
	}
}

void	flag_c(char *line, t_data *data)
{
	t_token	*tk;
	int		err;

	tk = NULL;
	if (!line)
	{
		ft_dprintf(2, "minishell: -c: option requires arguments\n");
		data->status = 2;
		return ;
	}
	err = tokenize(line, &tk, data);
	if (err)
	{
		data->status = err;
		return (token_clear(&tk));
	}
	data->ast_root = parse(&tk);
	token_clear(&tk);
	if (data->ast_root)
		data->status = exec_recursion(data->ast_root, data);
	ast_free(data->ast_root);
	fdlst_clear_leftovers(&data->fdlst);
}

void	execution_loop(t_data *data)
{
	struct termios	backup_term;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &backup_term);
		interactive_shell(data);
		tcsetattr(STDIN_FILENO, TCSANOW, &backup_term);
	}
	else
		non_interactive_shell(data);
}
