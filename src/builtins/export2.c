/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:29:57 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/25 18:36:23 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_env *ft_check_key(t_env **env, char *key)
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

static void ft_change_value(t_env *node, char *str)
{
    char *tmp;
    
    tmp = node->value;
    node->value = ft_strdup(str + ft_strlen(node->key) + 1);
    free(tmp);
    free(node->both);
    node->both = ft_strdup(str);
}

int check_export(char *arg, t_env *env)
{
    t_env *node;
    
    if (!ft_isalpha(arg[0]))
            printf("minishell: export: %s: not a valid identifier\n", arg);
    else if (ft_strchr(arg, '='))
    {
        node = ft_check_key(&env, arg);
        if (!node)
        {
            node = ft_envnew(arg);
            if (!node)
                return (1);
            ft_add_back(&env, node);
        }
        else
            ft_change_value(node, arg);
    }
    return (0);
}
