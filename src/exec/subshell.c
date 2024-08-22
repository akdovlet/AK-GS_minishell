/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:20:00 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/22 12:32:14 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_subshell(t_ast *ast, t_data *data)
{
    pid_t pid;
    t_pidlst node;

    pid = fork();
    if (pid < 0)
        return (perror("Fork failed\n"));
    else if(!pid)
        data->status = ft_recursive(ast->subshell_next, data);
    else
    {
        node = ft_lstnew_pidlst(pid);
        if (!node)
            return (1);
        ft_lstadd_back_pidlst(&data->pidlst, node);
    }
    return (0);
}