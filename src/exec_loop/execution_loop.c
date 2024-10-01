/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:31:58 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/01 16:26:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "AST.h"
#include "exec.h"

void	interactive_shell(t_data *data)
{
	char	*line;
	t_token	*tk;
	int		err;

	tk = NULL;
	err = 0;
	while (1)
	{
		line = readline("minishell$> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		add_history(line);
		err = tokenize(line, &tk, data->env);
		if (err)
			data->status = err;
		free(line);
		data->ast_root = parse(&tk);
		token_clear(&tk);
		if (data->ast_root)
			data->status = exec_recursion(data->ast_root, data);
		ast_free(data->ast_root);
	}
}

void	non_interactive_shell(t_data *data)
{
	char	*line;
	t_token	*tk;
	size_t	line_count;

	line_count = 0;
	tk = NULL;
	while (++line_count)
	{
		line = readline(NULL);
		if (!line)
			break ;
		add_history(line);
		if (tokenize(line, &tk, data->env) == 2)
		{
			data->status = 2;
			ft_dprintf(2, "minishell: line %d: %s\n", line_count, line);
			break ;
		}
		free(line);
		data->ast_root = parse(&tk);
		token_clear(&tk);
		if (data->ast_root)
			exec_recursion(data->ast_root, data);
		ast_free(data->ast_root);
	}
}

void	execution_loop(t_data *data)
{
	if (isatty(STDIN_FILENO) == 1)
		interactive_shell(data);
	else
		non_interactive_shell(data);
}
