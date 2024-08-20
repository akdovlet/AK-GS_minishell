/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:38:30 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/19 14:36:32 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"

// need correction for cd's call
int ft_exec(char *line, t_env *env)
{
    char **tab;
    
    tab = ft_split(line, ' ');
    if (is_builtins(tab[0]))
    {
        if (!ft_strcmp(tab[0], "echo"))
            ft_echo(tab, env);
        if (!ft_strcmp(tab[0], "cd"))
            cd(tab, env);
        else if (!ft_strcmp(tab[0], "pwd"))
            ft_pwd(tab, env);
        else if (!ft_strcmp(tab[0], "export"))
            ft_export(tab, env);
        else if (!ft_strcmp(tab[0], "unset"))
            unset(tab, env);
        else if (!ft_strcmp(tab[0], "env"))
            ft_env(tab, env);
        else if (!ft_strcmp(tab[0], "exit"))
            ft_exit(tab, env);
    }
    return (0);
}




int	exec_recursion(t_ast *ast, t_data *data)
{
	if (ast->type == PIPE)
	{
		ft_pipe_recusion(ast, data);
	}
	if (ast->type == CMD)
	{
		ft_exec_cmd(ast, data);
	}
	if (ast->type == OPERATOR)
	if (ast->type == REDIR)
	if (ast->type == SUBSHELL)
}

