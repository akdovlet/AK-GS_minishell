/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:00:28 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/18 13:01:39 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_whitespace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

int flag_n(char *str)
{
    int i;

    i = 0;
    if (str[i] != '-')
        return (1);
    i++;
    while (str[i])
    {
        if (str[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}

static int ft_echo_n(char **args)
{
    int i;
    int j;

    i = 2;
    j = 0;
    while (args[i])
    {
        if (!flag_n(args[i]) && !j)
            i++;
        else
            j++;
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
    if (!flag_n(args[1]))
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
