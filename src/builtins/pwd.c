/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:03:00 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/14 16:21:37 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(char **argv, t_env *env)
{
	char	*buf;

	(void)argv;
	(void)env;
	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror(PWDERROR);
		return (1);
	}
	if (ft_dprintf(STDOUT_FILENO, "%s\n", buf) == -1)
	{
		perror("minishell: pwd: write error");
		return (1);
	}
	free(buf);
	return (0);
}
