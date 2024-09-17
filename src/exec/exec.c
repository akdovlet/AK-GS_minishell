/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:38:30 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/17 17:24:31 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// gestion hard path
int ft_exec(t_ast *ast, t_data *data)
{
	expand_tab_of_cmd(ast->cmd, data);
	ast->cmd = ft_wildcard(ast->cmd);
	if (!ast->cmd)
		return (1);
    if (ft_is_builtins(ast->cmd[0]))
        ft_builtins(ast, data);
    else
        ft_exec_bin(ast, data);
    return (data->status);
}

int	exec_recursion(t_ast *ast, t_data *data)
{
	if (ast->type == PIPE_NODE)
		data->status = ft_pipe_recursion(ast, data);
	if (ast->type == CMD)
		data->status = ft_exec(ast, data);
	if (ast->type == WAIT_NODE)
		data->status = ft_wait_pid(ast, data);
	if (ast->type == OPERATOR)
		data->status = ft_operator(ast, data);
	if (ast->type == SUBSHELL)
		data->status = ft_subshell(ast, data);
	if (ast->type == REDIR)
		data->status = redir_node(ast, data);
	return (data->status);
}
