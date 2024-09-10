/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:05:02 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/10 11:35:21 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

 static int modif_oldpwd(t_env **env)
{
	t_env *tmp;

	tmp = ft_check_key(env, "OLDPWD");
	free(tmp->value);
	tmp->value = getcwd(NULL, 0);
	if (tmp->value == NULL)
		return (1);
	free(tmp->both);
	tmp->both = ft_strjoin("OLDPWD=", tmp->value);
	if (tmp->both == NULL)
		return (1);
	return (0);
}

static int modif_pwd(t_env **env)
{
	t_env *tmp;

	tmp = ft_check_key(env, "PWD");
	free(tmp->value);
	tmp->value = getcwd(NULL, 0);
	if (tmp->value == NULL)
		return (1);
	free(tmp->both);
	tmp->both = ft_strjoin("PWD=", tmp->value);
	if (tmp->both == NULL)
		return (1);
	return (0);
}

int	cd(char **args, t_env **env)
{
	if (!args[1])
	{
		if (modif_oldpwd(env))
			return (1);
		if (chdir(getenv("HOME")) != 0)
			return (perror("cd failed"), 1);
		if (modif_pwd(env))
			return (1);
	}
	else if (args[1] && args[2])
		ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
	else
	{
		if (modif_oldpwd(env))
			return (1);
		if (chdir(args[1]) != 0)
			return (perror("cd failed"), 1);
		if (modif_pwd(env))
			return (1);
	}
	return (0);
}
