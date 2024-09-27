/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:06:10 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/27 15:30:54 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

t_env	*env_new_key(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

bool	env_default_setup(t_data *data)
{
	t_env	*new;

	new = env_new_key(ft_strdup("PWD"), getcwd(NULL, 0));
	if (!new)
		return (1);
	env_add_back(&data->env, new);
	new = env_new_key(ft_strdup("SHLVL"), ft_strdup("1"));
	if (!new)
		return (1);
	env_add_back(&data->env, new);
	data->hardpath = ft_strdup(HARDPATH);
	if (!data->hardpath)
		return (1);
	return (0);
}

int	lstdup_env(t_env **dst, t_env *src)
{
	t_env	*new;
	t_env	*tmp;

	while (src)
	{
		new = env_new_key(ft_strdup(src->key), ft_strdup(src->value));
		if (!new)
			return (env_clear(dst), 1);
		if (!*dst)
			*dst = new;
		else
		{
			tmp = *dst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		src = src->next;
	}
	return (0);
}
