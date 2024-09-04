/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:24:46 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/04 16:02:47 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	redir_out(t_ast *ast, t_data *data)
{
	int	fd;

	if (ast->redir_type == OUT)
	{
		fd = open(ast->redir_filename, O_CREAT, O_RDWR, O_TRUNC, 0644);
		if (fd == -1)
			return (ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", ast->redir_filename, strerror(errno)),1);
	}
	else if (ast->redir_type == APPEND)
	{
		fd = open(ast->redir_filename, O_CREAT, O_RDWR, O_APPEND, 0644);
		if (fd == -1)
			return (ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", ast->redir_filename, strerror(errno)), 1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	redir_in(t_ast *ast, t_data *data)
{
	int	fd;

	fd = open(ast->redir_filename, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", ast->redir_filename, strerror(errno));
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	redir_hd(t_ast *ast, t_data *data)
{
	int		fd;
	int		tty;
	char	*line;

	line = NULL;
	tty = open("/dev/tty", O_RDWR);
	if (tty == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		return (1);
	}
	fd = open("/tmp", __O_TMPFILE | O_RDWR, 0644);
	if (fd == -1)
	{
		close(tty);
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", ast->redir_filename, strerror(errno));
		return (1);
	}
	while (1)
	{
		write(tty, "> ", 2);
		line = get_next_line(tty);
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, "minishell: ");
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	close(tty);
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
	if (type == IN || type == HERE_DOC)
		dup2(backup_fd, STDIN_FILENO);
	close(backup_fd);
}

int	redir_node(t_ast *ast, t_data *data)
{
	int	backup_fd;

	backup_fd = backup(ast->type);
	if (ast->redir_type == OUT || ast->redir_type == APPEND)
		data->status = redir_out(ast, data);
	else if (ast->redir_type == IN || ast->redir_type == HERE_DOC)
	{
		if (ast->redir_type == IN)
			data->status = redir_in(ast, data);
		else 
			data->status = redir_hd(ast, data);
	}
	if (data->status != 0)
		return (data->status);
	if (ast->redir_next)
		data->status = exec_recursion(ast->redir_next, data);
	restore_backup(backup_fd, ast->redir_type);
	return (data->status);
}
