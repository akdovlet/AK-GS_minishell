/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:33:23 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/25 14:37:26 by gautier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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

void unset(char **tab, t_env *env)
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
}
