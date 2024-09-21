/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:24:46 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/21 14:54:24 by akdovlet         ###   ########.fr       */
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

//tmp file flag does not work without lseek(), either write in a pipe
// or create my own tmp file. Also can not use strncmp to find delimiter.
int	redir_hd(t_ast *ast)
{
	int		tmp_file;
	int		tty;
	int		line_count;
	char	*line;

	line = NULL;
	line_count = 0;
	program_state = HD;
	tty = open("/dev/tty", O_RDWR);
	if (tty == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		return (1);
	}
	tmp_file = open("/tmp", __O_TMPFILE | O_RDWR, 0644);
	if (tmp_file == -1)
	{
		close(tty);
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", ast->redir_filename, strerror(errno));
		return (1);
	}
	while (1)
	{
		line_count++;
		write(tty, "> ", 2);
		line = get_next_line(tty);
		if (program_state == SIGINT)
		{
			printf("about to break\n");
			program_state = PARENT;
			return (130);
		}
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, "\nminishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", line_count, ast->redir_filename);
			break ;
		}
		if (!ft_strncmp(line, ast->redir_filename, ft_strlen(line) - 1))
		{
			free(line);
			break ;
		}
		write(tmp_file, line, ft_strlen(line));
		free(line);
	}
	lseek(tmp_file, 0, SEEK_SET);
	if (dup2(tmp_file, STDIN_FILENO) == -1)
		return (ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno)), 1);
	close(tmp_file);
	close(tty);
	program_state = PARENT;
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
	int	backup_fd;

	backup_fd = backup(ast->redir_type);
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
