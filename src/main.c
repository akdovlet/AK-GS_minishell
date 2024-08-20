/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/20 13:58:41 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "token.h"
#include "AST.h"

int main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_env	*my_env;
	t_token	*tk;
	t_ast 	*ast;

	if (ac != 1)
		return (1);
	my_env = NULL;
	tk = NULL;
	env_copy(&my_env, env);
	while (1)
	{
		line = readline(CYAN "minishell$> " RESET);
		if (!line)
			break ;
		add_history(line);
		tokenize(line, &tk);
		print_token(tk);
		ast = parse(&tk);
		ast_print(ast);
		free(line);
		ft_tkclear(&tk);
		ast_free(ast);
	}
	env_clear(&my_env);
	rl_clear_history();
	return (0);
}
