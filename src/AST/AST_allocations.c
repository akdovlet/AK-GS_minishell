/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_allocations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:48:36 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/25 17:02:06 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

t_ast	*ast_newcmd(t_cmdlst **lst)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
	{
		perror("minishell: ast_newcmd");
		cmdlst_clear(lst);
		return (NULL);
	}
	new->type = CMD;
	new->cmd = cmdlst_split(lst);
	if (!new->cmd)
	{
		perror("minishell: ast_newcmd");
		cmdlst_clear(lst);
		free(new);
		return (NULL);
	}
	return (new);
}

t_ast	*ast_newop(t_ast *left, t_type type, t_ast *right)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
	{
		perror("minishell: ast_newop");
		return (NULL);
	}
	new->type = OPERATOR;
	new->op_left = left;
	new->op_type = type;
	new->op_right = right;
	return (new);
}

t_ast	*ast_newredir(t_type type, char *filename, int fd)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
	{
		perror("minishell: ast_newredir");
		return (NULL);
	}
	new->type = REDIR;
	new->redir_fd = fd;
	new->redir_type = type;
	new->redir_filename = ft_strdup(filename);
	if (!new->redir_filename)
	{
		perror("minishell: ast_newredir");
		free(new);
		close(fd);
		return (NULL);
	}
	new->redir_next = NULL;
	return (new);
}

t_ast	*ast_newpipe(t_ast *left, t_ast *right)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
	{
		perror("minishell: ast_newpipe");
		return (NULL);
	}
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
	{
		perror("minishell: ast_newsubshell");
		return (NULL);
	}
	new->type = SUBSHELL;
	new->subshell_next = next;
	return (new);
}
