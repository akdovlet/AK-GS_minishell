/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:37:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/12 19:28:40 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "setup.h"

volatile sig_atomic_t	g_state;

int	setup_shell(t_data *data, char **env)
{
	*data = (t_data){};
	g_state = 0;
	if (env_setup(data, env))
		return (1);
	rl_outstream = stderr;
	setup_signals(data);
	return (0);
}
