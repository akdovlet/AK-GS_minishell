/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:31:58 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/17 19:44:30 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "AST.h"
#include "token.h"
#include "setup.h"

void	interactive_shell(t_data *data)
{
	char	*line;
	t_token	*tk;
	t_ast	*ast;

	tk = NULL;
	ast = NULL;
	while (1)
	{
		line = readline(CYAN "minishell$> " RESET);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		add_history(line);
		data->status = tokenize(line, &tk);
		free(line);
		ast = parse(&tk);
		token_clear(&tk);
		if (ast)
			data->status = exec_recursion(ast, data);
		ast_free(ast);
	}
}

void	non_interactive_shell(t_data *data)
{
	char	*line;
	t_token	*tk;
	t_ast	*ast;
	size_t	line_count;

	line_count = 1;
	tk = NULL;
	while (1)
	{
		line = readline(NULL);
		if (!line)
			break ;
		add_history(line);
		if (tokenize(line, &tk) == 2)
		{
			data->status = 2;
			ft_dprintf(STDERR_FILENO, "minishell: line %d: %s\n", line_count, line);
			break ;
		}
		free(line);
		ast = parse(&tk);
		token_clear(&tk);
		if (ast)
		{
			exec_recursion(ast, data);
			ast_free(ast);
		}
		line_count++;
	}
}

void	execution_loop(t_data *data)
{
	if (isatty(STDIN_FILENO) == 1)
		interactive_shell(data);
	else
		non_interactive_shell(data);
}
