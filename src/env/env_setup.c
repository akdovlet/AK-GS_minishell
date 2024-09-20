/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:06:10 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/20 14:32:02 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

char	*env_join_keyvalue(char *key, char *value)
{
	int		i;
	int		j;
	char	*fusion;

	i = -1;
	j = -1;
	fusion = malloc(sizeof(char) * ((ft_strlen(key) + (ft_strlen(value) + 2))));
	if (!fusion)
		return (NULL);
	while (key[++i])
		fusion[i] = key[i];
	fusion[i++] = '=';
	while (value[++j])
		fusion[i + j] = value[j];
	fusion[i + j] = '\0';
	return (fusion);
}

t_env	*env_new_key(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->both = env_join_keyvalue(key, value);
	if (!new->both)
		return (NULL);
	new->next = NULL;
	return (new);
}

// define a hard coded path
bool	env_default_setup(t_data *data)
{
	t_env	*new;

	new = env_new_key(ft_strdup("PWD"), getcwd(NULL, 0));
	if (!new)
		return (false);
	env_add_back(&data->env, new);
	new = env_new_key(ft_strdup("OLDPWD"), NULL);
	env_add_back(&data->env, new);
	new = env_new_key(ft_strdup("SHLVL"), ft_strdup("1"));
	env_add_back(&data->env, new);
	data->hardpath = ft_strdup(HARDPATH);
	return (true);
}

bool	env_setup(t_data *data, char **env)
{
	if (!env[0])
		return (env_default_setup(data));
	return (env_copy(&data->env, env));
}	
