/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:37:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/13 15:37:12 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "setup.h"
#include "env.h"

// void	interrupt_handler(void)

void	interrupt(int sig)
{
	if (sig == SIGINT)
	{
		printf("\nminishell$> ");
	}
	else if (sig == SIGTERM)
		printf("ctrl-d\n");
	else if (sig == SIGQUIT)
		printf("ctrl-\\\n");
}

void	setup_shell(t_data	*data, char	**env)
{
	struct sigaction sa;
	struct	termios termios_new;
	struct	termios termios_save;
	int		rc;

	rc = tcgetattr(0, &termios_save);
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios_new);
	*data = (t_data){};
	sa.sa_handler = interrupt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	env_setup(data, env);
}
