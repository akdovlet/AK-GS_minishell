/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:18:24 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/04 18:50:28 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(char **argv, t_env *env)
{
    if (argv[1])
        ft_dprintf(STDERR_FILENO, "env: too many arguments\n");
    else
    {
        while (env)
        {
            printf("%s\n", env->both);
            env = env->next;
        }
    }
}
