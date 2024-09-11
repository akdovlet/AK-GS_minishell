/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/10 15:39:43 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "token.h"
#include "AST.h"
#include "setup.h"

int main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_token	*tk;
	t_ast 	*ast;
	t_data	data;

	if (ac != 1)
		return (1);
	tk = NULL;
	setup_shell(&data, env);
	// env_print(data.env);
	while (1)
	{
		data.status = 0;
		line = readline(CYAN "minishell$> " RESET);
		if (!line)
			break ;
		add_history(line);
		tokenize(line, &tk);
		// print_token(tk);
		// env_print(data.env);
		ast = parse(&tk);
		// ast_print(ast);
		if (ast)
		{
			exec_recursion(ast, &data);
			ast_free(ast);
		}
		free(line);
		token_clear(&tk);
	}
	env_clear(&data.env);
	rl_clear_history();
	return (0);
}
