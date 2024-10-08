/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:37:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/02 19:56:30 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "setup.h"
#include "env.h"

int	*g_state;

int	setup_shell(t_data	*data, char	**env)
{
	*data = (t_data){};
	g_state = &data->status;
	if (env_setup(data, env))
		return (1);
	rl_outstream = stderr;
	setup_signals(data);
	return (0);
}
