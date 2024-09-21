/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:12:54 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/21 16:33:24 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

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
		return (NULL);
	while (env)
	{
		strs[i] = ft_strdup(env->both);
		if (!strs[i])
			return (ft_free(strs), NULL);
		i++;
		env = env->next;
	}
	strs[i] = NULL;
	return (strs);
}

bool	env_copy(t_env **cpy, char **env)
{
	int		i;
	t_env	*new;

	i = 0;
	while (env[i])
	{
		new = env_new(env[i]);
		if (!new)
			return (1);
		env_add_back(cpy, new);
		i++;
	}
	return (0);
}
