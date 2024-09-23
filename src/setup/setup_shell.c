/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:37:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/23 18:04:02 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "setup.h"
#include "env.h"

int	*program_state;

void	setup_shell(t_data	*data, char	**env)
{
	struct termios	config;

	if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, &config) < 0)
		perror("minishell: setup_shell");
	else
	{
		// config.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &config);
	}
	*data = (t_data){};
	program_state = &data->status;
	env_setup(data, env);
	setup_signals(data);
}
