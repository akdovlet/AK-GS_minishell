/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:05:02 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/20 18:50:48 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	modif_oldpwd(t_env **env)
{
	t_env	*tmp;

	tmp = ft_check_key(env, "OLDPWD");
	free(tmp->value);
	tmp->value = getcwd(NULL, 0);
	if (tmp->value == NULL)
		return (1);
	return (0);
}

static int	modif_pwd(t_env **env)
{
	t_env	*tmp;

	tmp = ft_check_key(env, "PWD");
	free(tmp->value);
	tmp->value = getcwd(NULL, 0);
	if (tmp->value == NULL)
		return (1);
	return (0);
}

// problem with error message 
// funct add / at the end of the path

char *add_slash(char *path)
{
	int i;
	char *tmp;

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

int chg_dir(char *path, t_env **env)
{
	char *pathn;
	
	if (modif_oldpwd(env))
		return (1);
	pathn = add_slash(path);
	if (!pathn)
		return (1);
	if (chdir(pathn))
	{
		if (access(pathn, F_OK))
			return (free(pathn),ft_dprintf(2, "minishell: cd: %s: Not a directory\n", path), 1);
		return (free(pathn),ft_dprintf(2, "minishell: cd: %s: No such file or directory\n", path), 1);
	}
	if (modif_pwd(env))
		return (free(pathn),1);
	return (free(pathn),0);
}
	

int	cd(char **args, t_env **env)
{
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		if (modif_oldpwd(env))
			return (1);
		if (chdir(getenv("HOME")))
			return (perror("minishell: cd failed\n"), 1);
		if (modif_pwd(env))
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
