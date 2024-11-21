/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:57:43 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/21 11:09:55 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "AST.h"
#include "exec.h"

char	*meet_in_the_middle(char *s1, char *s2, char c)
{
	int		i;
	int		j;
	char	*fusion;

	i = -1;
	j = -1;
	if (!s2)
		return (ft_strdup(s1));
	fusion = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!fusion)
		return (perror("minishell: meet_in_the_middle"), NULL);
	while (s1[++i])
		fusion[i] = s1[i];
	fusion[i++] = c;
	while (s2[++j])
		fusion[i + j] = s2[j];
	fusion[i + j] = '\0';
	return (fusion);
}

int	hard_path_check(char *cmd)
{
	struct stat	statbuf;

	if (!access(cmd, F_OK))
	{
		if (lstat(cmd, &statbuf) == -1)
			perror("lstat");
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_dprintf(2, "minishell: %s: Is a directory\n", cmd);
			return (126);
		}
		if (!access(cmd, X_OK))
			return (0);
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", cmd, strerror(errno));
		return (126);
	}
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", cmd, strerror(errno));
	return (127);
}

void	clear_exit(t_data *data, int code)
{
	ast_free(data->ast_root);
	env_clear(&data->env);
	env_clear(&data->export);
	fdlst_clear(&data->fdlst);
	pidlst_clear(&data->pidlst);
	free(data->hardpath);
	rl_clear_history();
	exit(code);
}
