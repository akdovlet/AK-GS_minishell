/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:31:58 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/14 19:29:02 by akdovlet         ###   ########.fr       */
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

int	non_interactive_shell(t_data *data)
{
	char	*line;
	t_token	*tk;
	t_ast	*ast;

	tk = NULL;
	while (1)
	{
		line = readline(NULL);
		if (!line)
			break ;
		add_history(line);
		if (!tokenize(line, &tk))
			break ;
		ast = parse(&tk);
		if (ast)
		{
			exec_recursion(ast, data);
			ast_free(ast);
		}
		free(line);
		token_clear(&tk);
	}
}

int	execution_loop(t_data *data)
{
	char	*line;
	t_token	*tk;
	t_ast 	*ast;
	int		line_count;

	tk = NULL;
	line_count = 1;
	while (1)
	{
		line = readline(CYAN "minishell$> " RESET);
		if (!line)
		{
			printf("exit\n");	
			break ;
		}
		add_history(line);
		if (!tokenize(line, &tk) && data.interactive_mode == false)
		{
			ft_dprintf(STDERR_FILENO, "minishell: line %d: `%s'\n", line_count, line);
			token_clear(&tk);
			break ;
		}
		ast = parse(&tk);
		if (ast)
		{
			exec_recursion(ast, &data);
			ast_free(ast);
		}
		free(line);
		token_clear(&tk);
		line_count++;
	}
	env_clear(&data.env);
	rl_clear_history();
	return (0);
}
