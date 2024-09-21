/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_wait_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:01:23 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/21 14:16:59 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

int	find_subshell(t_ast	*root)
{
	if (!root)
		return (0);
	else if (root->type == SUBSHELL)
		return (0);
	else if (root->type == CMD)
		return (1);
	else if (root->type == REDIR)
		return (find_subshell(root->redir_next));
	else if (root->type == PIPE_NODE)
	{
		if (!find_subshell(root->pipe_left))
			return (find_subshell(root->pipe_right));
		else
			return (1);
	}
	return (0);
}

t_ast	*ast_newwait(t_ast *wait_next)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = WAIT_NODE;
	new->wait_next = wait_next;
	return (new);
}
