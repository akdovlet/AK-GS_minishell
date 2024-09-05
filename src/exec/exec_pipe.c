/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:17:18 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/05 18:28:11 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_pipe_recursion(t_ast *ast, t_data *data)
{
	int	pipe_fd[2];
	int	backup_in;
	int	backup_out;

	backup_in = dup(STDIN_FILENO);
	backup_out = dup(STDOUT_FILENO);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	data->pipeline = true;
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2");
	close(pipe_fd[1]);
	data->status = exec_recursion(ast->pipe_left, data);
	dup2(backup_out, STDOUT_FILENO);
	close(backup_out);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup2");
	close(pipe_fd[0]);
	data->status = exec_recursion(ast->pipe_right, data);
	data->pipeline = 0;
	dup2(backup_in, STDIN_FILENO);
	close(backup_in);
	return (data->status);
}
