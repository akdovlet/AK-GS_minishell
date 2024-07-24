/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:04:41 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/24 10:35:14 by gschwand         ###   ########.fr       */
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
    unsigned char status;
    
    env_clear(&env);
    if (tab[1] && tab[2])
    {
        printf("exit\n");
        printf("minishell: exit: too many arguments\n");
        free_tab(tab);
        exit(1);
    }
    else
    if (tab[1])
    {
        status = (unsigned char) ft_atoi(tab[1]);
        free_tab(tab);
        exit(status);
    }
    else
        exit(0);
}
