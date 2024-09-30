/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/30 19:09:17 by akdovlet         ###   ########.fr       */
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
	struct termios	backup_term;

	if (ac != 1)
		return (1);
	tcgetattr(STDIN_FILENO, &backup_term);
	if (setup_shell(&data, env))
		return (1);
	execution_loop(&data);
	env_clear(&data.env);
	env_clear(&data.export);
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &backup_term);
	return (data.status);
}
