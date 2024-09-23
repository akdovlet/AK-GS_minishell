/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:04:41 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/23 14:48:31 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			printf("exit\n");
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", 
			str);
			exit(2);
		}
		i++;
	}
	return (0);
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_exit(char **tab, t_env *env, t_data *data)
{
	if (tab[1] && tab[2])
	{
		printf("exit\n");
		perror("minishell: exit: too many arguments\n");
		data->status = 127;
		return (127);
	}
	else if (tab[1])
	{
		check_only_digit(tab[1]);
		data->status = (unsigned char)ft_atoi(tab[1]);
		free_tab(tab);
		env_clear(&env);
		exit(data->status);
	}
	else
	{
		env_clear(&env);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
