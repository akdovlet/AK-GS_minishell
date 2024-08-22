/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:15:06 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/22 09:31:20 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// penser a free les nodes
static void	pip_wait_children(t_data *data)
{
	int	status;
    t_pidlst *node;
    t_pidlst *tmp;

    node = data->pidlst;
	while (node)
	{
		waitpid(node->pid, &status, 0);
		data->status = WEXITSTATUS(status);
        tmp = node;
		node->next;
        free(tmp->pid);
        free(tmp);
	}
}

int ft_wait_pid(t_ast *ast, t_data *data)
{
    if (!data->pidlst)
        return (data->status);
    ft_wait_children(data);
}
