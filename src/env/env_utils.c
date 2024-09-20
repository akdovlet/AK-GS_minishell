/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/20 18:51:55 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

// sudo cat /proc/1003/environ | tr '\0' '\n'
// displays env variables of given process
// can see that last cmd is not always last

char	*env_get_value(t_env *env, char *key)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	env_print(t_env *lst)
{
	while (lst)
	{
		ft_printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}

void	env_clear(t_env **lst)
{
	t_env	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->value);
		free((*lst)->both);
		free((*lst));
		*lst = tmp;
	}
}

t_env	*ft_check_key(t_env **env, char *key)
{
    t_env *tmp;
    
    tmp = *env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, ft_strlen(tmp->key)))
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}
