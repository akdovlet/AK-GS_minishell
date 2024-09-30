/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:12:54 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/30 15:59:38 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "minishell.h"

int	env_len(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_copy_to_char_arr(t_env *env)
{
	char	**strs;
	size_t	i;

	i = 0;
	if (!env)
		return (NULL);
	strs = malloc(sizeof(char *) * (env_len(env) + 1));
	if (!strs)
		return (perror("minishell: env_copy_to_char_arr"), NULL);
	while (env)
	{
		strs[i] = meet_in_the_middle(env->key, env->value, '=');
		if (!strs[i])
			return (ft_free(strs), NULL);
		i++;
		env = env->next;
	}
	strs[i] = NULL;
	return (strs);
}

t_env	*env_new_shlvl(char *var)
{
	t_env	*node;
	char	*tmp;
	int		lvl;

	lvl = 0;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = copy_key(var);
	if (!node->key)
		return (NULL);
	if (find_chr(var, '='))
	{
		lvl = ft_atoi(var + ft_strlen(node->key) + 1);
		lvl++;
		node->value = ft_itoa(lvl);
	}
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

bool	env_copy(t_env **cpy, char **env)
{
	int		i;
	int		check;
	t_env	*new;

	i = 0;
	check = 0;
	while (env[i])
	{
		if (!check && ft_strncmp(env[i], "SHLVL=", 7))
		{
			new = env_new_shlvl(env[i]);
			check = 1;
		}
		else
			new = env_new(env[i]);
		if (!new)
			return (env_clear(cpy), 1);
		env_add_back(cpy, new);
		i++;
	}
	return (0);
}
