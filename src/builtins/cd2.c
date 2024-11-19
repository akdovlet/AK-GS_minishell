/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:27:13 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/19 17:38:20 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	go_home(t_env **env)
{
	t_env	*tmp;

	tmp = env_get_node(*env, "HOME");
	if (tmp == NULL)
	{
		ft_dprintf(2, "minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(tmp->value))
		return (perror("minishell: cd failed"), 1);
	return (0);
}

char	*get_hard_path(char *path)
{
	char	*buf;
	char	*root;
	char	*hardpath;

	buf = NULL;
	if (!path)
		return (NULL);
	buf = getcwd(NULL, 0);
	if (!buf)
		return (free(path), perror("minishell: cd"), NULL);
	root = ft_strjoin(buf, "/");
	free(buf);
	hardpath = ft_strjoin(root, path);
	free(root);
	free(path);
	return (hardpath);
}
