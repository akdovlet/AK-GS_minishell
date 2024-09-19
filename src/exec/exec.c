/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:38:30 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/19 18:45:32 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// gestion hard path
char	*env_get_value(t_env *env, char *key)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*path_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*fusion;

	i = -1;
	j = -1;
	fusion = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!fusion)
		return (perror("minishell: path_join"), NULL);
	while (s1[++i])
		fusion[i] = s1[i];
	fusion[i++] = '/';
	while (s2[++j])
		fusion[i + j] = s2[j];
	fusion[i + j] = '\0';
	return (fusion);
}

int	find_path_loop(char **cmd_arr, char **path)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (path[i])
	{
		cmd_path = path_join(path[i], cmd_arr[0]);
		if (!cmd_path)
			return (ft_free(path), 1);
		if (!access(cmd_path, F_OK))
		{
			if (!access(cmd_path, X_OK))
			{
				free(cmd_arr[0]);
				cmd_arr[0] = cmd_path;
				return (0);
			}
			ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", cmd_arr[0], strerror(errno));
			return (126);
		}
		free(cmd_path);
		i++;
	}
	ft_dprintf(STDERR_FILENO, "minishell %s: %s\n", cmd_arr[0], strerror(errno));
	return (127);
}

int	hard_patch_check(char *str)
{
	
}

int	resolve_path(char **cmd, t_data *data)
{
	char	**path;
	char	*full_path;
	int		err;

	full_path = NULL;
	path = NULL;
	if (ft_strchr(cmd[0], '/'))
		return (0);
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

int	execute_prog(t_ast *ast, t_data *data)
{
	char	**env;
	int		err;

	err = resolve_path(ast->cmd, data);
	if (err)
		return (err);
	env = copy_env(data->env);
	execve(ast->cmd[0], ast->cmd, env);
	return (0);
}

int	command_node(t_ast *ast, t_data *data)
{
	expand_tab_of_cmd(ast->cmd, data->env);
	if (!ast->cmd)
		return (perror("minishell: command_node"), 1);
	// if (ft_is_builtins(ast->cmd[0]))
	// 	execute_builtin(ast, data);
	// else
		execute_prog(ast, data);
	return (data->status);
}

int ft_exec(t_ast *ast, t_data *data)
{
	expand_tab_of_cmd(ast->cmd, data->env);
	if (ast->cmd[1])
	{
		ast->cmd = ft_wildcard(ast->cmd);
		if (!ast->cmd)
			return (1);
	}
    if (ft_is_builtins(ast->cmd[0]))
        ft_builtins(ast, data);
    else
        ft_exec_bin(ast, data);
    return (data->status);
}

int	exec_recursion(t_ast *ast, t_data *data)
{
	if (ast->type == PIPE_NODE)
		data->status = ft_pipe_recursion(ast, data);
	if (ast->type == CMD)
		data->status = ft_exec(ast, data);
	if (ast->type == WAIT_NODE)
		data->status = ft_wait_pid(ast, data);
	if (ast->type == OPERATOR)
		data->status = ft_operator(ast, data);
	if (ast->type == SUBSHELL)
		data->status = ft_subshell(ast, data);
	if (ast->type == REDIR)
		data->status = redir_node(ast, data);
	return (data->status);
}
