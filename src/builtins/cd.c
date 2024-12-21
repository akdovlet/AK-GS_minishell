/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:23:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/21 11:53:41 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

void	change_pwd(t_env **env)
{
	t_env	*v1;
	t_env	*v2;

	v1 = env_get_real_node(env, "OLDPWD");
	v2 = env_get_real_node(env, "PWD");
	if (v1)
	{
		if (v1->value)
		{
			free(v1->value);
			v1->value = NULL;
		}
		if (v2)
			v1->value = v2->value;
	}
	if (v2)
		v2->value = getcwd(NULL, 0);
}

int	home(t_data *data, t_env **env)
{
	char	*str;

	str = env_get_value(*env, "HOME", data);
	if (!str)
	{
		ft_dprintf(2, "minishell: cd: HOME not set");
		return (1);
	}
	if (chdir(str))
	{
		ft_dprintf(2, "minishell: cd: %s: %s\n", str, strerror(errno));
		return (1);
	}
	change_pwd(env);
	return (0);
}

int	builtin_cd(t_data *data, char **args, t_env **env)
{
	if (!args[1])
		return (home(data, env));
	if (args[2])
		return (ft_dprintf(2, "minishell: cd: too many arguments\n"), 1);
	if (chdir(args[1]))
	{
		ft_dprintf(2, "minishell: cd: %s: %s\n", args[1], strerror(errno));
		return (1);
	}
	change_pwd(env);
	return (0);
}
