/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:15:06 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/21 16:32:57 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	pip_wait_children(t_data *data)
{
	int	status;
    t_pidlst *node;

    node = data->pidlst;
	while (node)
	{
		waitpid(node->pid, &status, 0);
		data->status = WEXITSTATUS(status);
		node->next;
	}
}

int ft_wait_pid(t_ast *ast, t_data *data)
{
    if (!data->pidlst)
        return (0);
    ft_wait_children(data)
}
