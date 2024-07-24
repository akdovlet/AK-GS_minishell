/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:04:41 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/24 09:11:14 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

// surement ici que l'on va devoir gerer toute la memoire
void ft_exit(char **tab, t_env *env)
{
    int status;
    
    env_clear(&env);
    if (tab[1])
    {
        status = ft_atoi(tab[1]);
        free_tab(tab);
        exit(status);
    }
    else
        exit(0);
}