/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:17:18 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/19 14:17:38 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_pipe_recusion(t_ast *ast, t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		retun (1);
	data->pipeline = true;
	data->write = fd[1];
	data->status = exec_recursion(ast->pipe_left, data);
	data->write = fd[0];
	data->status = exec_recursion(ast->pipe_right, data);
	close(fd[0]);
	close(fd[1]);
	data->pipeline = 0;
	return (data->status);
}