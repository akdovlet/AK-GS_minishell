/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:33:23 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/11 13:52:06 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void ft_lstdelone_env(t_env **env, t_env **delone)
{
    t_env *prev;

    prev = *env;
    while (ft_strcmp(prev->next->key, (*delone)->key) && prev->next)
        prev = prev->next;
    prev->next = (*delone)->next;
    free((*delone)->key);
    free((*delone)->value);
    free((*delone)->both);
    free((*delone));
}

int unset(char **tab, t_env *env)
{
    int i;
    t_env *tmp;

    i = 1;
    tmp = env;
    while (tab[i] && tmp)
    {
        if (!ft_strcmp(tab[i], tmp->key))
        {
            ft_lstdelone_env(&env, &tmp);
            tmp = env;
            i++;
        }    
        else
            tmp = tmp->next;
    }
    return (0);
}
