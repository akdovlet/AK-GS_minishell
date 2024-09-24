/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:36:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/24 18:53:00 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_hd(t_ast *ast)
{
	int	fd;

	fd = open(ast->redir_filename, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno)), 1);
	close(fd);
	return (0);
}
