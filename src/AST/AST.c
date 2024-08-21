/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:36:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/21 17:10:39 by akdovlet         ###   ########.fr       */
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
	if ((*tk)->type == WORD || is_redirect((*tk)->type))
		new = ast_newcmdlist(tk);
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
	new = parse_cmd(tk);
	if (*tk && is_redirect((*tk)->type))
		new = ast_newredir_lst(tk, new);
	return (new);
}

t_ast	*parse_pipe(t_token **tk)
{
	t_ast	*new;

	new = NULL;
	if (!(*tk) || !tk)
		return (NULL);
	new = parse_redirect(tk);
	while (*tk && (*tk)->type == PIPE)
	{
		eat_token(tk);
		new = ast_newpipe(new, parse_redirect(tk));
	}
	if (find_subshell(new))
		new = ast_newwait(new);
	return (new);
}

t_ast	*parse_operator(t_token **tk)
{
	t_ast	*new;
	t_type	tmp;

	if (!(*tk) || !tk)
		return (NULL);
	new = parse_pipe(tk);
	while (*tk && is_logical_operator((*tk)->type))
	{
		tmp = (*tk)->type;
		eat_token(tk);
		new = ast_newop(new, tmp, parse_pipe(tk));
	}
	return (new);
}

t_ast	*parse(t_token **tk)
{
	if (!*tk)
		return (NULL);
	return (parse_operator(tk));
}

// LOGICAL_OPERATOR (&& ||)
// SUBSHELL
// PIPE
// REDIR
// CMD
