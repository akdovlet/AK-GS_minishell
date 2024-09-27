/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:24:46 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/27 21:15:52 by akdovlet         ###   ########.fr       */
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
			return (ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", ast->redir_filename, strerror(errno)),1);
	}
	else
	{
		fd = open(ast->redir_filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", ast->redir_filename, strerror(errno)), 1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno)), 1);
	close(fd);
	return (0);
}

int	redir_in(t_ast *ast)
{
	int	fd;

	fd = open(ast->redir_filename, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", ast->redir_filename, strerror(errno));
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno)), 1);
	close(fd);
	return (0);
}

int	backup(t_type type)
{
	int	backup;

	if (type == OUT || type == APPEND)
		backup = dup(STDOUT_FILENO);
	if (type == IN || type == HERE_DOC)
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
	char	*expansion;

	backup_fd = backup(ast->redir_type);
	if (ast->redir_type != HERE_DOC)
	{
		expansion = expand_filename(ast->redir_filename, data->env);
		if (!expansion)
			return (ft_dprintf(2, "minishell: %s: ambiguous redirect\n", ast->redir_filename), 1);
		free(ast->redir_filename);
		ast->redir_filename = expansion;
	}
	fdlst_add_front(&data->fdlst, fdlst_new(backup_fd, true));
	if (ast->redir_type == OUT || ast->redir_type == APPEND)
		data->status = redir_out(ast);
	else if (ast->redir_type == IN || ast->redir_type == HERE_DOC)
	{
		if (ast->redir_type == IN)
			data->status = redir_in(ast);
		else 
			data->status = redir_hd(ast);
	}
	if (data->status != 0)
		return (data->status);
	if (ast->redir_next)
		data->status = exec_recursion(ast->redir_next, data);
	restore_backup(backup_fd, ast->redir_type);
	fdlst_delete_node(&data->fdlst, backup_fd);
	return (data->status);
}
