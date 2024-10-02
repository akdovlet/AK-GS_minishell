/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:36:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/02 20:58:40 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_hd(t_ast *ast)
{
	if (dup2(ast->redir_fd, STDIN_FILENO) == -1)
		return (ft_dprintf(2, "minishell: %s\n", strerror(errno)), 1);
	close(ast->redir_fd);
	return (0);
}
