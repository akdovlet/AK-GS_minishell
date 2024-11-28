/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/28 23:50:58 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "token.h"
#include "AST.h"
#include "setup.h"
#include "exec.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (setup_shell(&data, env))
		return (1);
	if (ac > 1 && !ft_strcmp(av[1], "-c"))
		return (flag_c(av[2], &data), data.status);
	execution_loop(&data);
	env_clear(&data.env);
	env_clear(&data.export);
	rl_clear_history();
	return (data.status);
}
