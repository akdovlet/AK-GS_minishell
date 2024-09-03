/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:38:30 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/03 12:01:41 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// gestion hard path
int ft_exec(t_ast *ast, t_data *data)
{
	printf("ast->cmd[1] = %s\n", ast->cmd[1]);
	expand_tab_of_cmd(ast->cmd, data->env);
	printf("ast->cmd[1] = %s\n", ast->cmd[1]);
	if (ast->cmd[1])
	{
		if (ft_wildcard(ast->cmd))
			return (false);
	}
    if (ft_is_builtins(ast->cmd[0]))
        ft_builtins(ast, data);
    else
        ft_exec_bin(ast, data);
    return (0);
}

int	exec_recursion(t_ast *ast, t_data *data)
{
	if (ast->type == PIPE_NODE)
		ft_pipe_recusion(ast, data);
	if (ast->type == CMD)
		ft_exec(ast, data);
	if (ast->type == WAIT_NODE)
		ft_wait_pid(ast, data);
	if (ast->type == OPERATOR)
		ft_operator(ast, data);
	if (ast->type == SUBSHELL)
		ft_subshell(ast, data);
	// if (ast->type == REDIR)
	return (data->status);
}
