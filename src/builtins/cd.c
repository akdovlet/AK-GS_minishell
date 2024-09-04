/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:05:02 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/04 18:50:00 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd(char **args, t_env *env)
{
	(void)env;
	if (!args[1])
	{
		if (chdir(getenv("HOME")) != 0)
			return (perror("cd failed"), 1);
	}
	else if (args[1] && args[2])
		ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
	else
	{
		if (chdir(args[1]) != 0)
			return (perror("cd failed"), 1);
	}
	return (0);
}
