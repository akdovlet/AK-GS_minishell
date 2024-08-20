/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:06:10 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/24 18:51:44 by akdovlet         ###   ########.fr       */
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
bool	env_default_setup(t_env **my_env)
{
	t_env	*new;

	new = env_new_key("PWD", getcwd(NULL, 0));
	if (!new)
		return (false);
	env_add_back(my_env, new);
	new = env_new_key("SHLVL", "1");
	env_add_back(my_env, new);
	return (true);
}

bool	env_setup(t_env **my_env, char **env)
{
	if (!env[0])
		return (env_default_setup(my_env));
	return (env_copy(my_env, env));
}	
