/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:00:50 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/25 18:20:46 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (*program_state != 69)
				rl_redisplay();
		*program_state = 130;
	}
}

void	signal_handler(int sig)
{
	// if (program_state == PARENT)
		parent_handler(sig);
	// if (program_state == CHILD)
	// 	child_handler(sig);
	// if (program_state == HD)
	// 	here_doc_handler(sig);
}

void	setup_signals(t_data *data)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	data->sa = sa;
	// sa.sa_flags = SA_RESETHAND;
	// sa.sa_handler = 0;
	// sigaction(SIGINT, &sa, NULL);
}
