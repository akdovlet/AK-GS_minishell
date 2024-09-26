/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:53:21 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/26 11:32:57 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expand.h"
#include "minishell.h"
#include "exec.h"
#include "setup.h"
#include "AST.h"

int	find_path_loop(char **cmd_arr, char **path)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (path[i])
	{
		cmd_path = meet_in_the_middle(path[i], cmd_arr[0], '/');
		if (!cmd_path)
			return (1);
		if (!access(cmd_path, F_OK))
		{
			if (!access(cmd_path, X_OK))
			{
				free(cmd_arr[0]);
				cmd_arr[0] = cmd_path;
				return (0);
			}
			ft_dprintf(2, "minishell: %s: %s\n", cmd_arr[0], strerror(errno));
			return (126);
		}
		free(cmd_path);
		i++;
	}
	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd_arr[0]);
	return (127);
}

int	resolve_path(char **cmd, t_data *data)
{
	char	**path;
	char	*full_path;
	int		err;

	full_path = NULL;
	path = NULL;
	if (ft_strchr(cmd[0], '/'))
		return (hard_path_check(cmd[0]));
	full_path = env_get_value(data->env, "PATH");
	if (!full_path)
	{
		if (data->hardpath)
			path = ft_split(data->hardpath, ':');
		else
			return (hard_path_check(cmd[0]));
	}
	else
		path = ft_split(full_path, ':');
	if (!path)
		return (perror("minishell: resolve_path"), 1);
	err = find_path_loop(cmd, path);
	ft_free(path);
	return (err);
}

void	forked_execution(t_ast *ast, t_data *data)
{
	int		err;
	char	**env;

	fdlst_close_in_child(data->fdlst);
	err = resolve_path(ast->cmd, data);
	if (err)
		clear_exit(data, err);
	env = env_copy_to_char_arr(data->env);
	if (!env)
		clear_exit(data, 1);
	execve(ast->cmd[0], ast->cmd, env);
	ft_dprintf(2, "minishell: %s: %s\n", ast->cmd[0], strerror(errno));
	ft_free(env);
	clear_exit(data, 1);
}

int	execute_prog(t_ast *ast, t_data *data)
{
	pid_t		pid;
	t_pidlst	*new;

	ast->cmd = expand_tab_of_cmd(ast->cmd, data);
	if (!ast->cmd)
		return (perror("minishell: command_node"), 1);
	if (ast->cmd[1])
	{
		ast->cmd = ft_wildcard(ast->cmd);
		if (!ast->cmd)
			return (1);
	}
	pid = fork();
	if (pid < 0)
		return (perror("minishell: execute_prog"), 1);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		forked_execution(ast, data);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		new = ft_lstnew_pidlst(pid);
		if (!new)
			return (1);
		ft_lstadd_back_pidlst(&data->pidlst, new);
	}
	return (0);
}

int	command_node(t_ast *ast, t_data *data)
{
	ast->cmd = expand_first_cmd(ast->cmd, data);
	if (!ast->cmd || !ast->cmd[0])
		return (0);
	if (ft_is_builtins(ast->cmd[0]))
	{
		if (ft_strcmp(ast->cmd[0], "export") != 0 && ft_strcmp(ast->cmd[0],
				"unset") != 0)
		{
			ast->cmd = expand_tab_of_cmd(ast->cmd, data);
			if (!ast->cmd)
				return (perror("minishell: command_node"), 1);
			if (ast->cmd[1])
			{
				ast->cmd = ft_wildcard(ast->cmd);
				if (!ast->cmd)
					return (1);
			}
		}
		return (ft_builtins(ast, data));
	}
	else
		return (execute_prog(ast, data));
}
