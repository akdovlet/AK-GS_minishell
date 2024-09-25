/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 07:21:54 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/25 17:53:26 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_env_lst(t_env *lst)
{
	while (lst)
	{
		if (lst->value)
			printf("export %s=%s\n", lst->key, lst->value);
		else
			printf("export %s\n", lst->key);
		lst = lst->next;
	}
}

int	ft_export(char **args, t_data *data)
{
	int	i;
	int	e;
	int	tmp;

	e = 0;
	tmp = 0;
	i = 1;
	if (!args[i])
		return (print_env_lst(data->export), 0);
	while (args[i])
	{
		tmp = check_export(args[i], data);
		if (tmp)
			e = tmp;
		i++;
	}
	return (e);
}
