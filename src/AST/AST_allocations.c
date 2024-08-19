/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_allocations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:48:36 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/19 12:30:00 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

t_ast	*ast_newcmd(t_cmdlist **lst)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = CMD;
	new->cmd = split_cmdlst(lst);
	return (new);
}

t_ast	*ast_newop(t_ast *left, t_type type, t_ast *right)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = OPERATOR;
	new->op_left = left;
	new->op_type = type;
	new->op_right = right;
	return (new);
}

t_ast	*ast_newredir(t_type type, char *filename)
{
	t_ast	*new;
	
	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = REDIR;
	new->redir_type = type;
	new->file_name = ft_strdup(filename);
	new->redir_next = NULL;
	return (new);
}

t_ast	*ast_newredir_push_root(t_ast *redir_next, t_type type, char *filename)
{
	t_ast	*new;
	
	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = REDIR;
	new->redir_type = type;
	new->file_name = filename;
	new->redir_next = redir_next;
	return (new);
}

t_ast	*ast_newpipe(t_ast *left, t_ast *right)
{
	t_ast *new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = PIPE_NODE;
	new->pipe_left = left;
	new->pipe_right = right;
	return (new);
}

t_ast	*ast_newsubshell(t_ast *next)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (perror("ast_newsubshell malloc"), NULL);
	new->type = SUBSHELL;
	new->subshell_next = next;
	return (new);
}
