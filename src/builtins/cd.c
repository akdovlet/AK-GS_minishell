/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:05:02 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/22 12:24:03 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **args)
{
	if (args == NULL)
	{
		ft_putstr_fd("minishell: expected argument to \"cd\"\n", STDERR_FILENO);
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
