/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:36:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/15 15:12:05 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

t_ast	*ast_newcmd(t_token **tk)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = CMD;
	new->lst = NULL;
	new->cmd = ft_strdup((*tk)->value);
	eat_token(tk);
	while (*tk && (*tk)->type == WORD)
	{
		new->cmd = ft_strjoin(new->cmd, (*tk)->value);
		eat_token(tk);
	}
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

t_ast	*ast_newredir(t_ast *redir_next, t_token **tk)
{
	t_ast	*new;
	
	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = REDIR;
	new->redir_type = (*tk)->type;
	eat_token(tk);
	new->file_name = ft_strdup((*tk)->value);
	new->redir_next = redir_next;
	eat_token(tk);
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

t_ast	*parse_cmd(t_token **tk)
{
	t_ast	*new;

	new = NULL;
	if (!(*tk) || !tk)
		return (NULL);
	fprintf(stderr, "parse_cmd\n");
	if ((*tk)->type == WORD)
		new = ast_newcmd(tk);
	else if ((*tk)->type == PARENTHESIS_L)
	{
		eat_token(tk);
		new = parse(tk);
		new = ast_newsubshell(new);
		if ((*tk)->type == PARENTHESIS_R)
			eat_token(tk);
	}
	return (new);
}

t_ast	*parse_redirect(t_token **tk)
{
	t_ast	*new;

	new = NULL;
	if (!(*tk) || !tk)
		return (NULL);
	fprintf(stderr, "parse_redirect\n");
	new = parse_cmd(tk);
	while (*tk && is_redirect((*tk)->type))
	{
		if (!new || new->type == CMD || new->type == SUBSHELL)
			new = ast_newredir(new, tk);
		else if (!new || (new && new->type == REDIR))
		{
			new->redir_next = parse(tk);
		}
	}
	return (new);
}

t_ast	*parse_pipe(t_token **tk)
{
	t_ast	*new;

	new = NULL;
	if (!(*tk) || !tk)
		return (NULL);
	fprintf(stderr, "parse_pipe\n");
	new = parse_redirect(tk);
	while (*tk && (*tk)->type == PIPE)
	{
		fprintf(stderr, "in parse pipe\n");
		eat_token(tk);
		new = ast_newpipe(new, parse_redirect(tk));
	}
	return (new);
}

t_ast	*parse_operator(t_token **tk)
{
	t_ast	*new;
	t_type	tmp;

	if (!(*tk) || !tk)
		return (NULL);
	fprintf(stderr, "parse_operator\n");
	new = parse_pipe(tk);
	while (*tk && is_logical_operator((*tk)->type))
	{
		fprintf(stderr, "in op\n");
		tmp = (*tk)->type;
		eat_token(tk);
		new = ast_newop(new, tmp, parse_pipe(tk));
	}
	return (new);
}

t_ast	*parse(t_token **tk)
{
	fprintf(stderr, "parse\n");
	if (!*tk)
		return (NULL);
	return (parse_operator(tk));
}
