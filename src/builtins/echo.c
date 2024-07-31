/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:00:28 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/26 12:36:49 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    ft_putstr_fd("\n", 1);
    return (0);
}

// int main()
// {
//     char *args1[] = {"echo", "Bonjour", "le", "monde", NULL};
//     char *args2[] = {"echo", "-n", "Bonjour", "sans", "nouvelle", "ligne", NULL};

//     // Test de la fonction echo sans l'option -n
//     echo(args1);

//     // Test de la fonction echo avec l'option -n
//     echo(args2);

//     return 0;
// }