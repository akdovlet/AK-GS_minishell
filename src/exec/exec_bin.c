/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:14:48 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/22 12:05:39 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_cmd(char **cmd, char **envp)
{
	char	**path_env;
	char	**path_cmd;
	char	*path;

	path_env = ft_split(find_path_env(envp), ':');
	path_cmd = find_path_cmd(path_env, cmd[0]);
	if (!path_cmd)
		return (free_tab(path_env), NULL);
	path = ft_strdup(path_cmd[0]);
	free_tab(path_env);
	free_tab(path_cmd);
	return (path);
}

int	ft_execve_path(char **cmd, char **envp)
{
	char	*path_cmd;

	path_cmd = find_cmd(cmd, envp);
	if (path_cmd)
	{
		execve(path_cmd, cmd, envp);
		free(path_cmd);
	}
	ft_puterror("command not found: ", cmd[0]);
	exit(EXIT_FAILURE);
}

int	ft_execve_hard_path(char **cmd, char **envp)
{
	execve(cmd[0], cmd, envp);
	free_tab(cmd);
	ft_putstr_fd("execve failed\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

// cree une fonction que me recopie data->env dans un tableau de chaine de caractere
char **ft_ll_tab(t_env *env)
{
    int len;
    char **tab;
    t_env *tmp;
    int i;

    i = 0;
    tmp = env;
    i = ft_lstsize_env(env);
    tab = malloc(sizeof(char *) * (i + 1));
    if (!tab)
        return (NULL);
    i = 0;
    tmp = env;
    while (tmp)
    {
        tab[i] = ft_strdup(tmp->both);
        if (!tab[i])
            return (free_tab(tab), NULL);
        i++;
        tmp = tmp->next;
    }
    tab[i] = NULL;
    return (tab);
}

int ft_check_path(t_data *data)
{
    t_env *node;

    node = data->env;
    while (node)
    {
        if (!ft_strcmp(node->key, "PATH"))
            return ;
        node = node->next;
    }
    if (data->)
        node = ft_lstnew_env(data->path); //pas la bonne ft il y en a une plus approprie
    else
        node = ft_lstnew_env(".");
    if (!node)
        return (1);
    ft_lstadd_back_env(&data->env, node);
    return (0);
}

int ft_exec_bin(t_ast *ast, t_data *data)
{
    char **env;
    pid_t pid;
    t_pidlst *new;

    ft_check_path(data);
    env = ft_ll_tab(data->env);
    pid = fork();
    if (pid < 0)
        return (perror("fork failed\n"), 1);
    else if (pid == 0)
    {
        if (access(ast->cmd[0], F_OK) == -1)
            data->status = ft_execve_path(ast->cmd, env);
        else
            data->status = ft_execve_hard_path(ast->cmd, env);
    }
    else
    {
        new = ft_lstnew_pidlst(pid);
        if (!new)
            return (data->status);
        ft_lstadd_back_pidlst(&data->pidlst, new);
    }
    free_tab(env);
    return (0);
}
