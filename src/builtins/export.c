/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 07:21:54 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/19 13:20:41 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_env_lst(t_env *lst)
{
	int	err;

	err = 0;
	while (lst)
	{
		if (lst->value)
			err = ft_dprintf(STDOUT_FILENO, "export %s=\"%s\"\n", lst->key,
					lst->value);
		else
			err = ft_dprintf(STDOUT_FILENO, "export %s\n", lst->key);
		lst = lst->next;
	}
	if (err == -1)
		perror("minishell: export: write error");
	return (err);
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
		return (print_env_lst(data->export));
	while (args[i])
	{
		tmp = check_export(args[i], data);
		if (tmp)
			e = tmp;
		i++;
	}
	return (e);
}
