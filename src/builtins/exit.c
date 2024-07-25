/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:04:41 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/25 12:39:56 by gautier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void free_tab(char **tab)
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

void ft_exit(char **tab, t_env *env)
{
    unsigned char status;

    if (tab[1] && tab[2])
    {
        printf("exit\n");
        printf("minishell: exit: too many arguments\n");
    }
    else if (tab[1])
    {
        ft_printf("ok\n");
        status = (unsigned char) ft_atoi(tab[1]);
        free_tab(tab);
        env_clear(&env);
        exit(status);
    }
    else
    {
        env_clear(&env);
        exit(0);
    }
}
