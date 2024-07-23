/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 07:21:54 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/23 09:54:45 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static bool	copy_env_env(t_env **cpy, t_env *env)
{
	t_env	*new;

	while (env)
	{
		new = ft_envnew(env->both);
		if (!new)
			return (false);
		ft_add_back(cpy, new);
        env = env->next;
	}
	return (true);
}

static void ft_sort_alpha(t_env **env)
{
    t_env *tmp;
    t_env *tmp2;
    char *tmp_key;
    char *tmp_value;
    
    tmp = *env;
    while (tmp)
    {
        tmp2 = tmp->next;
        while (tmp2)
        {
            if (ft_strcmp(tmp->key, tmp2->key) > 0)
            {
                tmp_key = tmp->key;
                tmp_value = tmp->value;
                tmp->key = tmp2->key;
                tmp->value = tmp2->value;
                tmp2->key = tmp_key;
                tmp2->value = tmp_value;
            }
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }
}

static int ft_sort_alpha_env(t_env *env)
{
    t_env *cpy;
    
    if (copy_env_env(&cpy, env) == false)
        return (1);
    ft_sort_alpha(&cpy);
    print_env(cpy);
    env_clear(&cpy);
    return (0);
}

// need a sort for empty string
// Var doit commencer par alpha
// Args doit contenir "="
// retour export seulememt pour premier caractere pas alpha ": not a valid identifier"
int ft_export(char **args, t_env *env)
{
    int i;
    t_env *node;
    
    i = 1;
    if (!args[i])
    {
        ft_sort_alpha_env(env);
        return (0);
    }
    while (args[i])
    {
        if (!ft_isalpha(args[i][0]))
            printf("minishell: export: `%s': not a valid identifier\n", args[i]);
        else if (ft_strchr(args[i], '='))
        {
            node = ft_envnew(args[i]);
            if (!node)
                return (1);
            ft_add_back(&env, node);
        }
    }
    return (0);
}
