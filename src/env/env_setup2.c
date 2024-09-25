/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:42 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/25 17:13:04 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	ft_sort_alpha(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*tmp3;

	tmp = *env;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->key, tmp2->key) > 0)
			{
				tmp3 = tmp->key;
				tmp->key = tmp2->key;
				tmp2->key = tmp3;
				tmp3 = tmp->value;
				tmp->value = tmp2->value;
				tmp2->value = tmp3;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

int	export_default_setup(t_data *data)
{
	t_env	*new;

	if (lstdup_env(&data->export, data->env))
		return (1);
	new = env_new_key(ft_strdup("OLDPWD"), NULL);
	if (!new)
		return (1);
	env_add_back(&data->export, new);
	ft_sort_alpha(&data->export);
	return (0);
}

int	env_export_default_setup(t_data *data)
{
	if (env_default_setup(data))
		return (1);
	if (export_default_setup(data))
		return (1);
	return (0);
}

int	env_export_copy(t_data *data, char **env)
{
	data->env = NULL;
	data->export = NULL;
	if (env_copy(&data->env, env))
		return (1);
	if (export_default_setup(data))
		return (1);
	return (0);
}

bool	env_setup(t_data *data, char **env)
{
	if (!env[0])
	{
		if (env_export_default_setup(data))
            return (1);
		return (0);
	}
	return (env_export_copy(data, env));
}
