/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:36:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/17 13:53:17 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

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
		if (new->type != SUBSHELL)
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
		new = ast_newredir_push_root(new, (*tk)->type, ft_strdup((*tk)->next->value));
		eat_token(tk);
		eat_token(tk);
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

// LOGICAL_OPERATOR (&& ||)
// SUBSHELL
// PIPE
// REDIR
// CMD
