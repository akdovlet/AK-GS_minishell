/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/20 18:50:31 by gschwand         ###   ########.fr       */
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
	setup_shell(&data, env);
	execution_loop(&data);
	env_clear(&data.env);
	rl_clear_history();
	return (0);
}
