/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:15:06 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/23 21:10:59 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "setup.h"

static void	pip_wait_children(t_data *data)
{
	int			status;
	t_pidlst	*node;
	t_pidlst	*tmp;

	node = data->pidlst;
	status = 0;
	while (node)
	{
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
	if (WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	if (WTERMSIG(status) == SIGQUIT)
		write(1, "Quit\n", 5);
	fprintf(stderr, "status is %d\n", data->status);
	data->pidlst = NULL;
	sigaction(SIGINT, &data->sa, NULL);
}

int	ft_wait_pid(t_ast *ast, t_data *data)
{
	data->status = exec_recursion(ast->wait_next, data);
	if (!data->pidlst)
		return (data->status);
	pip_wait_children(data);
	return (data->status);
}
