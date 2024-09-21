/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:14:48 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/20 18:52:25 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_puterror(char *str_error, char *str)
{
	ft_putstr_fd(str_error, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

int	ft_execve_path(char **cmd, char **envp, t_data *data)
{
	char	*path_cmd;

	path_cmd = find_cmd(cmd, envp);
	if (path_cmd)
	{
		execve(path_cmd, cmd, envp);
		free(path_cmd);
	}
	ft_dprintf(2, "minishell: %s: command not found\n", cmd[0]);
    data->status = 127;
	exit(data->status);
}

// attention au message d'erreur
int	ft_execve_hard_path(char **cmd, char **envp, t_data *data)
{
	execve(cmd[0], cmd, envp);
	free_tab(cmd);
	ft_dprintf(2, "minishell: %s: command not found\n", cmd[0]);
    data->status = 127;
	exit(data->status);
}

char *both_env(t_env *env)
{
    char *str;
    char *tmp;

    str = ft_strjoin(env->key, "=");
    if (!str)
        return (NULL);
    tmp = ft_strjoin(str, env->value);
    free(str);
    return (tmp);
}

// cree une fonction que me recopie data->env dans un tableau de chaine de caractere
// plus de both donc cree une fonction qui concatene key et value et egale
char **ft_ll_tab(t_env *env)
{
    char **tab;
    t_env *tmp;
    int i;

    tmp = env;
    i = ft_lstsize_env(env);
    tab = malloc(sizeof(char *) * (i + 1));
    if (!tab)
	{
		perror("minishell: ft_ll_tab");
        return (NULL);
	}
    i = 0;
    tmp = env;
    while (tmp)
    {
        tab[i] = both_env(tmp);
        if (!tab[i])
            return (free_tab(tab), NULL);
        i++;
        tmp = tmp->next;
    }
    tab[i] = NULL;
    return (tab);
}

// faux modif ne doit pas etre dans l'env
int ft_check_path(t_data *data)
{
    t_env *node;

    node = data->env;
    while (node)
    {
        if (!ft_strcmp(node->key, "PATH"))
            return (0);
        node = node->next;
    }
    if (data->hardpath)
        node = env_new(data->hardpath);
    else
        node = env_new("PATH=.");
    if (!node)
        return (1);
    env_add_back(&data->env, node);
    return (0);
}

void    close_all(void)
{
    int i;

    i = 3;
    while (i < 256)
    {
        close(i);
        i++;
    }
}

int ft_find_chr_exec(char *str, char c)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (-1);
}

int ft_exec_bin(t_ast *ast, t_data *data)
{
    char		**env;
    pid_t		pid;
    t_pidlst	*new;

    ft_check_path(data);
    env = ft_ll_tab(data->env);
	if (!env)
		return (1);
    pid = fork();
    if (pid < 0)
        return (perror("fork failed\n"), 1);
    else if (pid == 0)
    {
        fdlst_close_in_child(data->fdlst);
        if (ft_find_chr_exec(ast->cmd[0], '/') >= 0)
            ft_execve_hard_path(ast->cmd, env, data);
        else
            ft_execve_path(ast->cmd, env, data);
    }
    else
    {
		// signal_wait_state();
        new = ft_lstnew_pidlst(pid);
        if (!new)
            return (1);
        ft_lstadd_back_pidlst(&data->pidlst, new);
    }
    free_tab(env);
    return (0);
}
