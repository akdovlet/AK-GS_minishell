/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:15:06 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/20 15:43:59 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	pip_wait_children(t_data *data)
{
	int	status;
	t_pidlst *node;
	t_pidlst *tmp;

	node = data->pidlst;
	while (node)
	{
		// signal_wait_state();
		waitpid(node->pid, &status, 0);
		if (WIFSIGNALED(status))
			data->status = 128 + WTERMSIG(status);
		else
			data->status = WEXITSTATUS(status);
		tmp = node;
		node = node->next;
		free(tmp);
		tmp = NULL;
	}
	// reset_signal_state();
	data->pidlst = NULL;
}

int	ft_wait_pid(t_ast *ast, t_data *data)
{
	data->status = exec_recursion(ast->wait_next, data);
	if (!data->pidlst)
		return (data->status);
	pip_wait_children(data);
	return (data->status);
}
