/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:17:18 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/08 13:28:43 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <signal.h>

//int	left_pipe_setup(t_ast *ast, t_data *data)
//int	right_pipe_setup(t_ast *ast, t_data *data)

int ft_pipe_recursion(t_ast *ast, t_data *data)
{
	int	pipe_fd[2];
	int	backup_in;
	int	backup_out;

	backup_out = dup(STDOUT_FILENO);
	fdlst_add_back(&data->fdlst, fdlst_new(backup_out, true));
	data->pipeline = true;
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2");
	close(pipe_fd[1]);
	fdlst_add_back(&data->fdlst, fdlst_new(pipe_fd[0], true));
	data->status = exec_recursion(ast->pipe_left, data);
	dup2(backup_out, STDOUT_FILENO);
	close(backup_out);
	// fdlst_dont_close_in_child(data->fdlst, backup_out);
	backup_in = dup(STDIN_FILENO);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup2");
	fdlst_add_back(&data->fdlst, fdlst_new(backup_in, true));
	close(pipe_fd[0]);
	// fdlst_dont_close_in_child(data->fdlst, pipe_fd[0]);
	// fdlst_dont_close_in_child(data->fdlst, backup_out);
	data->status = exec_recursion(ast->pipe_right, data);
	data->pipeline = 0;
	dup2(backup_in, STDIN_FILENO);
	close(backup_in);
	fdlst_clear(&data->fdlst);
	return (data->status);
}
