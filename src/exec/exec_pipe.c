/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:17:18 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/11 12:57:52 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// exec_recursion don't return data->status
int ft_pipe_recusion(t_ast *ast, t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	data->pipeline = true;
	data->write = fd[1];
	exec_recursion(ast->pipe_left, data);
	data->write = fd[0];
	exec_recursion(ast->pipe_right, data);
	close(fd[0]);
	close(fd[1]);
	data->pipeline = 0;
	return (data->status);
}
