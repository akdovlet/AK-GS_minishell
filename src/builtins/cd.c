/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:05:02 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/28 23:23:01 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	modif_oldpwd(t_env **env)
{
	t_env	*tmp;

	tmp = env_get_node(*env, "OLDPWD");
	if (tmp == NULL)
		return (0);
	free(tmp->value);
	tmp->value = env_get_node(*env, "PWD")->value;
	if (tmp->value == NULL)
		return (1);
	return (0);
}

static int	modif_pwd(char *path, t_env **env)
{
	t_env	*tmp;

	tmp = env_get_node(*env, "PWD");
	if (tmp == NULL)
		return (0);
	tmp->value = path;
	if (tmp->value == NULL)
		return (1);
	return (0);
}

char	*add_slash(char *path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
		i++;
	if (path[i - 1] != '/')
	{
		tmp = ft_strjoin(path, "/");
		if (tmp == NULL)
			return (NULL);
		path = tmp;
	}
	else
	{
		tmp = ft_strdup(path);
		if (tmp == NULL)
			return (NULL);
		path = tmp;
	}
	return (path);
}

int	chg_dir(char *path, t_env **env)
{
	char	*pathn;

	pathn = add_slash(path);
	if (pathn[0] != '/')
		pathn = get_hard_path(pathn);
	if (!pathn)
		return (1);
	if (chdir(pathn))
	{
		printf("pathn: %s\n", pathn);
		if (access(pathn, F_OK))
		{
			ft_dprintf(2, "minishell123: cd: %s: Not a directory\n", path);
			return (free(pathn), 1);
		}
		ft_dprintf(2, "minishell: cd: %s: No such file or directory\n", path);
		return (free(pathn), 1);
	}
	if (modif_oldpwd(env))
		return (free(pathn), 1);
	if (modif_pwd(pathn, env))
		return (free(pathn), 1);
	return (0);
}

int	cd(char **args, t_env **env)
{
	char	*path;

	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		if (go_home(env))
			return (1);
		if (modif_oldpwd(env))
			return (1);
		path = get_hard_path(ft_strdup(args[1]));
		if (modif_pwd(path, env))
			return (1);
	}
	else if (args[1] && args[2])
		ft_dprintf(2, "minishell: cd: too many arguments\n");
	else
	{
		if (chg_dir(args[1], env))
			return (1);
	}
	return (0);
}
