/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:24:46 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/06 18:53:33 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	redir_out(t_ast *ast)
{
	int	fd;

	if (ast->redir_type == OUT)
	{
		fd = open(ast->redir_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (ft_dprintf(2, "minishell: %s: %s\n", \
			ast->redir_filename, strerror(errno)), 1);
	}
	else
	{
		fd = open(ast->redir_filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (ft_dprintf(2, "minishell: %s: %s\n", \
			ast->redir_filename, strerror(errno)), 1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (ft_dprintf(2, "minishell: %s\n", strerror(errno)), 1);
	close(fd);
	return (0);
}

int	redir_in(t_ast *ast)
{
	int	fd;

	fd = open(ast->redir_filename, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "minishell: %s: %s\n", \
		ast->redir_filename, strerror(errno));
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (ft_dprintf(2, "minishell: %s\n", strerror(errno)), 1);
	}
	close(fd);
	return (0);
}

int	backup(t_type type)
{
	int	backup;

	if (type == OUT || type == APPEND)
		backup = dup(STDOUT_FILENO);
	else
		backup = dup(STDIN_FILENO);
	return (backup);
}

void	restore_backup(int backup_fd, t_type type)
{
	if (type == OUT || type == APPEND)
		dup2(backup_fd, STDOUT_FILENO);
	else if (type == IN || type == HERE_DOC)
		dup2(backup_fd, STDIN_FILENO);
	close(backup_fd);
}

int	redir_node(t_ast *ast, t_data *data)
{
	int		backup_fd;

	if (ast->redir_type != HERE_DOC && redir_expand(ast, data))
		return (1);
	backup_fd = backup(ast->redir_type);
	fdlst_add_front(&data->fdlst, fdlst_new(backup_fd, true));
	if (ast->redir_type == OUT || ast->redir_type == APPEND)
		data->status = redir_out(ast);
	else if (ast->redir_type == IN)
		data->status = redir_in(ast);
	else
		data->status = redir_hd(ast, data);
	if (data->status != 0)
	{
		fdlst_delete_node(&data->fdlst, backup_fd);
		close(backup_fd);
		return (data->status);
	}
	if (ast->redir_next)
		data->status = exec_recursion(ast->redir_next, data);
	restore_backup(backup_fd, ast->redir_type);
	fdlst_delete_node(&data->fdlst, backup_fd);
	return (data->status);
}
