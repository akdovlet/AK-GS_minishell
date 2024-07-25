/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:38:30 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/25 12:43:19 by gautier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

// need correction for cd's call
int ft_exec(char *line, t_env *env)
{
    char **tab;
    
    tab = ft_split(line, ' ');
    if (is_builtins(tab[0]))
    {
        if (!ft_strcmp(tab[0], "echo"))
            ft_echo(tab);
        if (!ft_strcmp(tab[0], "cd"))
            cd(tab);
        else if (!ft_strcmp(tab[0], "pwd"))
            ft_pwd();
        else if (!ft_strcmp(tab[0], "export"))
            ft_export(tab, env);
        else if (!ft_strcmp(tab[0], "unset"))
            unset(tab, env);
        else if (!ft_strcmp(tab[0], "env"))
            ft_env(env);
        else if (!ft_strcmp(tab[0], "exit"))
            ft_exit(tab, env);
    }
    return (0);
}
