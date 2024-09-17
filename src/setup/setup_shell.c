/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:37:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/17 20:03:26 by akdovlet         ###   ########.fr       */
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
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGTERM)
		printf("ctrl-d\n");
	else if (sig == SIGQUIT)
		printf("ctrl-\\\n");
}

void	setup_shell(t_data	*data, char	**env)
{
	struct sigaction	sa;
	struct termios		termios_new;
	struct termios		termios_save;
	int		rc;

	rc = tcgetattr(0, &termios_save);
	termios_new = termios_save;
	// termios_new.c_lflag &= ~ECHOCTL;
	// termios_new.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	rc = tcsetattr(0, 0, &termios_new);
	sa.sa_handler = interrupt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	*data = (t_data){};
	if (isatty(STDIN_FILENO))
		data->interactive_mode = true;
	else
		data->interactive_mode = false;
	env_setup(data, env);
}
