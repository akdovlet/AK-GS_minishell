/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:21:07 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/24 11:24:06 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_is_builtins(char *cmd)
{
    // printf("ft_is_builtins\n");
    if (!ft_strcmp(cmd, "echo"))
        return (1);
    if (!ft_strcmp(cmd, "cd"))
        return (1);
    if (!ft_strcmp(cmd, "pwd"))
        return (1);
    if (!ft_strcmp(cmd, "export"))
        return (1);
    if (!ft_strcmp(cmd, "unset"))
        return (1);
    if (!ft_strcmp(cmd, "env"))
        return (1);
    if (!ft_strcmp(cmd, "exit"))
        return (1);
    return (0);
}

// Check when I need to use **env and when I need to use *env
// export for sure
// unset maybe
int ft_exec_builtins(t_ast *ast, t_data *data)
{
    if (!ft_strcmp(ast->cmd[0], "echo"))
        data->status = ft_echo(ast->cmd, data->env);
    if (!ft_strcmp(ast->cmd[0], "cd"))
        data->status = cd(ast->cmd, &data->env);
    if (!ft_strcmp(ast->cmd[0], "pwd"))
        data->status = ft_pwd(ast->cmd, data->env);
    if (!ft_strcmp(ast->cmd[0], "export"))
        data->status = ft_export(ast->cmd, data);
    if (!ft_strcmp(ast->cmd[0], "unset"))
        data->status = unset(ast->cmd, data); 
    if (!ft_strcmp(ast->cmd[0], "env"))
        data->status = ft_env(ast->cmd, data->env);
    if (!ft_strcmp(ast->cmd[0], "exit"))
        data->status = ft_exit(ast->cmd, data->env, data);
    return (0);
}

int ft_fork_builtins(t_ast *ast, t_data *data)
{
    pid_t pid;
    t_pidlst *new;

    pid = fork();
    if (pid < 0)
        return (perror("fork failed\n"), 1);
    else if (pid == 0)
    {
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
        fdlst_close_in_child(data->fdlst);
        ft_exec_builtins(ast, data); //need to free who need to be freed
        clear_exit(data, data->status);
    }
	if (pid != 0)
    {
		signal(SIGINT, SIG_IGN);
        new = ft_lstnew_pidlst(pid);
        if (!new)
            return (1);
        ft_lstadd_back_pidlst(&data->pidlst, new);
    }
    return (0);
}

int ft_builtins(t_ast *ast, t_data *data)
{
    if (data->pipeline == 0)
        ft_exec_builtins(ast, data);
    else
        ft_fork_builtins(ast, data);
    return (0);
}
