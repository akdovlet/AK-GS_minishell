/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:08:20 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/19 17:10:03 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_path_env(char **env)
{
	int	i;

	i = 0;
	while (1)
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

void	free_tab_2(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}

char	**find_path_cmd(char **path_env, char *cmd)
{
	int		i;
	char	*path_cmd[3];
	char	**path_cmd_split;

	i = 0;
	while (path_env[i])
	{
		path_cmd[0] = ft_strjoin(path_env[i], "/");
		path_cmd[1] = ft_strjoin(path_cmd[0], cmd);
		path_cmd[2] = NULL;
		if (!access(path_cmd[1], X_OK))
		{
			path_cmd_split = ft_split(path_cmd[1], ' ');
			return (free_tab_2(path_cmd), path_cmd_split);
		}
		free_tab_2(path_cmd);
		i++;
	}
	return (NULL);
}

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
