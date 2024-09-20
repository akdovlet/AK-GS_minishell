/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:18:24 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/20 14:20:30 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(char **argv, t_env *env)
{
    if (argv[1])
        ft_dprintf(STDERR_FILENO, "env: too many arguments\n");
    else
    {
        while (env)
        {
            printf("%s=%s\n", env->key, env->value);
            env = env->next;
        }
    }
    return (0);
}
