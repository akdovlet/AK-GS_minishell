/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:37:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/10 17:02:15 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "setup.h"
#include "env.h"

// void	interrupt_handler(void)

void	interrupt(int sig)
{
	if (sig == SIGINT)
		printf("^C\n");
	else if (sig == SIGTERM)
		printf("ctrl-d\n");
	else if (sig == SIGQUIT)
		printf("ctrl-\\\n");
}

void	setup_shell(t_data	*data, char	**env)
{
	struct sigaction sa;

	*data = (t_data){};
	sa.sa_handler = interrupt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	env_setup(data, env);
}
