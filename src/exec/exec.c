/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:38:30 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/02 16:28:38 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include "exec.h"
#include "env.h"

int	exec_recursion(t_ast *ast, t_data *data)
{
	if (ast->type == PIPE_NODE)
		pipe_node(ast, data);
	if (ast->type == CMD)
		command_node(ast, data);
	if (ast->type == WAIT_NODE)
		ft_wait_pid(ast, data);
	if (ast->type == OPERATOR)
		ft_operator(ast, data);
	if (ast->type == SUBSHELL)
		ft_subshell(ast, data);
	if (ast->type == REDIR)
		redir_node(ast, data);
	return (data->status);
}
