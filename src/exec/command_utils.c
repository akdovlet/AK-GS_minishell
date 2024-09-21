/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:57:43 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/21 16:15:25 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "AST.h"
#include "exec.h"

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

int	hard_path_check(char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (0);
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", cmd, strerror(errno));
		return (126);
	}
	return (127);
}

void	clear_exit(t_data *data, int code)
{
	ast_free(data->ast_root);
	env_clear(&data->env);
	fdlst_clear(&data->fdlst);
	pidlst_clear(&data->pidlst);
	free(data->hardpath);
	rl_clear_history();
	exit(code);
}
