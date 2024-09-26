/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:06:10 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/26 15:45:33 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

// recode la meme fonction que env_join_keyvalue mais sans i = - 1 et j = -1
char	*env_join_keyvalue2(char *key, char *value)
{
	int		i;
	int		j;
	char	*fusion;

	i = 0;
	j = 0;
	fusion = malloc(sizeof(char) * ((ft_strlen(key) + (ft_strlen(value) + 2))));
	if (!fusion)
		return (perror("minishell: env_join_keyvalue2"), NULL);
	while (key[i])
	{
		fusion[i] = key[i];
		i++;
	}
	fusion[i++] = '=';
	if (value)
	{
		while (value[j])
		{
			fusion[i + j] = value[j];
			j++;
		}
	}
	fusion[i + j] = '\0';
	return (fusion);
}

t_env	*env_new_key(char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (perror("minishell: ft_strdup"), NULL);
	if (!value)
		return (perror("minishell: ft_strdup"), free(key), NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (free(key), free(value), perror("minishell: env_new_key"), NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

// define a hard coded path
bool	env_default_setup(t_data *data)
{
	t_env	*new;

	new = env_new_key(ft_strdup("PWD"), ft_strdup(getcwd(NULL, 0)));
	if (!new)
		return (1);
	env_add_back(&data->env, new);
	new = env_new_key(ft_strdup("SHLVL"), ft_strdup("1"));
	if (!new)
		return (1);
	env_add_back(&data->env, new);
	data->hardpath = ft_strdup(HARDPATH);
	if (!data->hardpath)
		return (perror("minishell: ft_strdup"), 1);
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
