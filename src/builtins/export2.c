/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:29:57 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/27 16:10:56 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_export_env(t_env *env, char *str)
{
	t_env	*node;
	char	*key_tmp;

	if (check_alnum_str(str) != 1)
		return (ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n",
				str), 1);
	key_tmp = ft_strndup(str, ft_strchr(str, '=') - str);
	if (!key_tmp)
		return (1);
	node = ft_check_key(&env, key_tmp);
	free(key_tmp);
	if (!node)
	{
		node = env_new(str);
		if (!node)
			return (1);
		env_add_back(&env, node);
	}
	else
	{
		if (ft_change_value(node, str))
			return (1);
	}
	return (0);
}

int	check_key_export(t_env *export, char *str)
{
	t_env	*node;

	node = ft_check_key(&export, str);
	if (!node)
	{
		node = env_new(str);
		if (!node)
			return (1);
		env_add_back(&export, node);
	}
	return (0);
}

int	export_of_value(t_env *export, char *str)
{
	t_env	*node;
	char	*key_tmp;

	key_tmp = ft_strndup(str, ft_strchr(str, '=') - str);
	if (!key_tmp)
		return (1);
	node = ft_check_key(&export, key_tmp);
	free(key_tmp);
	if (!node)
	{
		node = env_new(str);
		if (!node)
			return (1);
		env_add_back(&export, node);
	}
	else
	{
		if (ft_change_value(node, str))
			return (1);
	}
	return (0);
}

int	check_export_export(t_env *export, char *str)
{
	int	i;

	i = check_alnum_str(str);
	if (!i)
		return (ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n",
				str), 1);
	else if (i == 2)
	{
		if (check_key_export(export, str))
			return (1);
		return (0);
	}
	if (export_of_value(export, str))
		return (1);
	return (0);
}

int	check_export(char *arg, t_data *data)
{
	if (check_export_export(data->export, arg))
		return (1);
	if (check_export_env(data->env, arg))
		return (1);
	return (0);
}
