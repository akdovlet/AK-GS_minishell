/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:38:30 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/21 10:06:45 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_exec(t_ast *ast, t_data *data)
{
    if (ft_is_builtins(ast->cmd[0]))
        ft_builtins(ast, data);
    else
        ft_exec_bin(ast, data);
    return (0);
}

int	exec_recursion(t_ast *ast, t_data *data)
{
	if (ast->type == PIPE)
		ft_pipe_recusion(ast, data);
	if (ast->type == CMD)
		ft_exec(ast, data);
	if (ast->type == OPERATOR)
	if (ast->type == REDIR)
	if (ast->type == SUBSHELL)
}
