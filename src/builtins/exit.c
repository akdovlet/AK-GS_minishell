/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:04:41 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/25 18:11:30 by gschwand         ###   ########.fr       */
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
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
				str);
			return (2);
		}
		i++;
	}
	return (0);
}

int	ft_exit(char **tab, t_data *data)
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
		printf("exit\n");
		data->status = check_only_digit(tab[1]);
		data->status = (unsigned char)ft_atoi(tab[1]);
		clear_exit(data, data->status);
	}
	else
	{
		printf("exit\n");
		clear_exit(data, data->status);
	}
	return (0);
}
