/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:00:28 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/18 09:56:55 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_whitespace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

static int ft_echo_n(char **args)
{
    int i;

    i = 2;
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    return (0);
}

// correction maybe not good
int ft_echo(char **args, t_env *env)
{
    (void)env;
    int i;

    i = 1;
    if (!args[1])
    {
        ft_putstr_fd("\n", 1);
        return (0);
    }
    if (args[1] && !ft_strcmp(args[1], "-n"))
        return (ft_echo_n(args));
    while (args[i])
    {
        if (!args[i][0])
            i++;
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    ft_putstr_fd("\n", 1);
    return (0);
}
