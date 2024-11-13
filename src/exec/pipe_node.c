/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:17:18 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/13 21:30:59 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	left_pipe_setup(t_data *data, int pipe_fd[2], int backup_fd[2])
{
	backup_fd[1] = dup(STDOUT_FILENO);
	if (backup_fd[1] == -1)
		return (perror("minishell: left_pipe_setup"), 1);
	if (fdlst_add_front(&data->fdlst, fdlst_new(backup_fd[1], true)))
	{
		close(backup_fd[1]);
		perror("minishell: left_pipe_setup");
		return (1);
	}
	if (pipe(pipe_fd) == -1)
	{
		close(backup_fd[1]);
		return (perror("minishell: left_pipe_setup"), 1);
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close(backup_fd[1]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (perror("minishell: left_pipe_setup"), 1);
	}
	close(pipe_fd[1]);
	fdlst_add_front(&data->fdlst, fdlst_new(pipe_fd[0], true));
	return (0);
}

int	right_pipe_setup(t_data *data, int pipe_fd[2], int backup_fd[2])
{
	if (dup2(backup_fd[1], STDOUT_FILENO) == -1)
	{
		close(pipe_fd[0]);
		close(backup_fd[1]);
		return (perror("minishell: right_pipe_setup"), 1);
	}
	close(backup_fd[1]);
	fdlst_delete_node(&data->fdlst, backup_fd[1]);
	backup_fd[0] = dup(STDIN_FILENO);
	if (backup_fd[0] == -1)
		return (close(pipe_fd[0]), perror("minishell: right_pipe_setup"), 1);
	if (fdlst_add_front(&data->fdlst, fdlst_new(backup_fd[0], true)))
	{
		close(backup_fd[0]);
		close(pipe_fd[0]);
		return (perror("minishell: right_pipe_setup"), 1);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(backup_fd[0]);
		close(pipe_fd[0]);
		return (perror("minishell: right_pipe_setup"), 1);
	}
	fdlst_delete_node(&data->fdlst, pipe_fd[0]);
	return (close(pipe_fd[0]), 0);
}

int	pipe_node(t_ast *ast, t_data *data)
{
	int	pipe_fd[2];
	int	backup_fd[2];

	if (left_pipe_setup(data, pipe_fd, backup_fd))
	{
		fdlst_clear(&data->fdlst);
		return (-1);
	}
	data->fork = true;
	data->status = exec_recursion(ast->pipe_left, data);
	if (right_pipe_setup(data, pipe_fd, backup_fd))
	{
		fdlst_clear(&data->fdlst);
		data->fork = false;
		return (-1);
	}
	data->fork = true;
	data->status = exec_recursion(ast->pipe_right, data);
	data->fork = false;
	dup2(backup_fd[0], STDIN_FILENO);
	close(backup_fd[0]);
	fdlst_delete_node(&data->fdlst, backup_fd[0]);
	return (data->status);
}
