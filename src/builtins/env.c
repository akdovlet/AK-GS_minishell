/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:18:24 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/25 18:27:44 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	ft_env(char **argv, t_env *env)
{
    if (argv[1])
        printf("env: too many arguments\n");
    else
    {
        while (env)
        {
            ft_putstr_fd(env->both, 1);
            ft_putstr_fd("\n", 1);
            env = env->next;
        }
    }
}
