/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:29:57 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/20 18:37:32 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_change_value(t_env *node, char *str)
{
	char	*tmp;

	tmp = node->value;
	if (ft_strchr(str, '='))
		node->value = ft_strdup(str + ft_strlen(node->key) + 1);
	else
		node->value = NULL;
	free(tmp);
}

// ATTENTION CETTE FONCTION RETURNE 0 SI CONDITIONS FAUSSE
int check_alnum_str(char *str)
{
	int i;
	
	i = 0;
	if (!ft_isalpha(str[0]))
	{
		return (ft_dprintf(2, "minishell: export: %s: not a valid identifier\n", str), 0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			return (ft_dprintf(2, "minishell: export: %s: not a valid identifier\n", str), 0);
		}
		i++;
	}
	if (str[i] != '=')
		return (2);
	return (1);
}

int check_export_env(t_env *env, char *str)
{
	t_env	*node;

	if (check_alnum_str(str) != 1)
		return (1);
	node = ft_check_key(&env, str);
	if (!node)
	{
		node = env_new(str);
		if (!node)
			return (1);
		env_add_back(&env, node);
	}
	else
		ft_change_value(node, str);
	return (0);
}

int check_export_export(t_env *export, char *str)
{
	t_env	*node;

	if (!check_alnum_str(str))
		return (printf("sortie\n"), 1);
	node = ft_check_key(&export, str);
	if (!node)
	{
		node = env_new(str);
		if (!node)
			return (1);
		env_add_back(&export, node);
	}
	else
		ft_change_value(node, str);
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
