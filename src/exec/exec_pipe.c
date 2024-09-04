/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:17:18 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/04 18:34:44 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_pipe_recursion(t_ast *ast, t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	data->pipeline = true;
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("dup2");
	close(fd[1]);
	data->status = exec_recursion(ast->pipe_left, data);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("dup2");
	close(fd[0]);
	data->status = exec_recursion(ast->pipe_right, data);
	data->pipeline = 0;
	return (data->status);
}
