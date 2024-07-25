/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:05:02 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/25 18:22:27 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	cd(char **args, t_env *env)
{
	(void)env;
	if (!args[1])
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("minishell");
		}
	}
	else if (args[1] && args[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("minishell");
		}
	}
	return (0);
}
