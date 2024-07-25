/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:05:02 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/25 13:54:40 by gautier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **args)
{
	if (!args[1])
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("minishell");
		}
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
