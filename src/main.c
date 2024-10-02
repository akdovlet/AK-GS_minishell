/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/02 17:23:23 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "token.h"
#include "AST.h"
#include "setup.h"
#include "exec.h"

int main(int ac, char **av, char **env)
{
	(void)av;
	t_data	data;

	if (ac != 1)
		return (1);
	if (setup_shell(&data, env))
		return (1);
	execution_loop(&data);
	env_clear(&data.env);
	env_clear(&data.export);
	rl_clear_history();
	return (data.status);
}
