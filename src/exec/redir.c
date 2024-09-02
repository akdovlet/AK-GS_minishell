/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:24:46 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/02 14:30:08 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	redir_out(t_ast *ast, t_data *data)
{
	int	fd;

	if (!file_check(ast->redir_filename))
		return (1);
	if (ast->redir_type == OUT)
	{
		fd = open(ast->redir_filename, O_CREAT, O_RDWR, O_TRUNC, 644);
		if (fd == -1)
			return (ft_dprintf(STDERR_FILENO, "bash: %s: %s\n", ast->redir_filename, strerror(errno)),1);
	}
	else if (ast->redir_type == APPEND)
	{
		fd = open(ast->redir_filename, O_CREAT, O_RDWR, O_APPEND, 644);
		if (fd == -1)
			return (ft_dprintf(STDERR_FILENO, "bash: %s: %s\n", ast->redir_filename, strerror(errno)), 1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	redir_in(t_ast *ast, t_data *data)
{
	int	fd;

	fd = open(ast->redir_filename, O_RDONLY);
}

int	redir_node(t_ast *ast, t_data *data)
{
	if (!ast)
		return (0);
	if (ast->redir_type == OUT || ast->redir_type == APPEND)
		data->status = redir_out(ast, data);
	else if (ast->redir_type == IN)
		data->status = redir_in(ast, data);
	else if (ast->redir_type == HERE_DOC)
		data->status = redir_hd(ast, data);
	if (data->status != 0)
		return (data->status);
	if (ast->redir_next)
		data->status = exec_recursion(ast->redir_next, data);
	dup2(data->read, STDIN_FILENO);
	dup2(data->write, STDIN_FILENO);
	return (data->status);
}
