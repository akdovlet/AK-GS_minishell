/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/20 17:34:26 by gschwand         ###   ########.fr       */
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
	// env_print(data.export);
	while (1)
	{
		line = readline(CYAN "minishell$> " RESET);
		if (!line)
			break ;
		add_history(line);
		tokenize(line, &tk);
		ast = parse(&tk);
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
