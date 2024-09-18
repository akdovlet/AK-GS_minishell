/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:00:50 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/18 19:22:43 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_handler(int sig)
{
	
}

void	here_doc_handler(int sig)
{
	
}

void	signal_handler(int sig)
{
	if (program_state == PARENT)
		parent_handler(sig);
	if (program_state == CHILD)
		child_handler(sig);
	if (program_state == HD)
		here_doc_handler(sig);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_flags = SA_RESETHAND;
	sa.sa_handler = 0;
	sigaction(SIGINT, &sa, NULL);
}
