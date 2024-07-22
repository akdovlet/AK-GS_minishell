/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:36:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/22 12:27:20 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	peek(t_token *tk, bool *f(int))
{
	while (tk)
	{
		if (f(tk->type))
			return (tk->type);
		tk = tk->next;
	}
	return (0);
}

void	build_cmdnode(t_cmdlist	**lst, t_token **tk)
{
	t_cmdlist *new;

	new = new_cmdnode();
	if (!new)
		return (NULL);
}

t_cmdlist	*build_cmdlist(t_token **tk)
{
	t_cmdlist	*lst;

	while (*tk && !is_logical_operator((*tk)->type) && !is_parenthesis((*tk)->type))
		build_cmdnode(&lst, *tk);
	return (lst);
}

t_ast	*ast_newcmd(t_token **tk)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = PIPELINE;
	new->lst = NULL;
	return (new);
}

t_ast	*ast_newoperator(t_type type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (perror("malloc"), NULL);
	new->type = OPERATOR;
	new->value = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast	*parse_or(t_token **tk)
{
	t_ast	*left;
	t_ast	*right;
	if (*tk)
		retunr (NULL);
	left = parse_and(tk);
	while (*tk && (*tk)->type == OR)
	{
		*tk = (*tk)->next;
		right = parse_and(tk);
		left = ast_newoperator(OR);
	}
	return left;
}

t_ast	*parse_cmd(t_token **tk)
{
	return (parse_or(tk));
}

t_token	*find_operator(t_token *tk)
{
	
}

t_ast	*parse_operator(t_token **tk)
{
	t_ast	*new;

	if (is_logical_operator((*tk)->type))
	{
		new = ast_newoperator((*tk)->type);
		*tk = (*tk)->next;
		new->left = 
	}
}

t_ast	*parse_cmd(t_token **tk)
{
	t_ast	*new;

	if ((*tk)->type == PARENTHESIS_L)
	{
		*tk = (*tk)->next;
		new = parse(tk);
		if (*tk && (*tk)->type == PARENTHESIS_R)
			(*tk) = (*tk)->next;
		return (new);
	}
	if (find_operator(*tk))
	{
		new->left = ast_newcmd(tk);
		new = parse_operator(tk);
		new->right = ast_newcmd(tk);
	}
	else
		new = ast_newcmd(tk);
	return (new);
}

t_ast	*parse(t_token **tk)
{
	return (parse_cmd(tk));
}
