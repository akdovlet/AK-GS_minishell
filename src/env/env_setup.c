/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:06:10 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/30 18:21:14 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

t_env	*env_new_key(char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (perror("minishell: ft_strdup"), NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (free(key), free(value), perror("minishell: env_new_key"), NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	env_default_setup(t_data *data)
{
	t_env	*new;
	t_env	*new2;

	new = env_new_key(ft_strdup("PWD"), getcwd(NULL, 0));
	if (!new)
		return (1);
	env_add_back(&data->env, new);
	new2 = env_new_key(ft_strdup("SHLVL"), ft_strdup("1"));
	if (!new2)
		return (1);
	env_add_back(&data->env, new2);
	data->hardpath = ft_strdup(HARDPATH);
	if (!data->hardpath)
		return (perror("minishell: ft_strdup"), 1);
	return (0);
}

int	env_lstdup(t_env **dst, t_env *src)
{
	t_env	*new;

	while (src)
	{
		new = env_new_key(ft_strdup(src->key), ft_strdup(src->value));
		if (!new)
			return (env_clear(dst), 1);
		env_add_back(dst, new);
		src = src->next;
	}
	return (0);
}
