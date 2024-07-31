/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/31 18:47:45 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

// sudo cat /proc/1003/environ | tr '\0' '\n'
// displays env variables of given process
// can see that last cmd is not always last
void	last_cmd(t_env **my_env, char *str)
{
	t_env	*tmp;
	t_env	*runner;

	runner = *my_env;
	while (runner->next && ft_strcmp(runner->next->key, "_"))
		runner = runner->next;
	if (ft_strcmp(runner->next->key, "_"))
	{
		free(runner->next->key);
		free(runner->next->value);
		free(runner->next->both);
		tmp = runner->next->next;
		free(runner->next);
		runner->next = ft_envnew(str);
		if (!runner->next)
			return (env_clear(my_env), exit(EXIT_FAILURE));
		runner->next->next = tmp;
	}
	else
	{
		runner->next = ft_envnew("_=");
		if (!runner->next)
			return (env_clear(my_env), exit(EXIT_FAILURE));
	}
}

void	print_env(t_env *lst)
{
	while (lst)
	{
		ft_printf("%s\n", lst->both);
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
		free((*lst));
		*lst = tmp;
	}
}

t_env *ft_check_key(t_env **env, char *key)
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
