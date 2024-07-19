/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:36:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/19 18:39:42 by akdovlet         ###   ########.fr       */
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
t_ast	*ast_newcmd(t_token *tk)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = PIPELINE;
	new->lst = build_cmd_line(tk);
	return (new);
}

t_ast	*ast_newoperator(t_token *tk, t_ast *left, t_ast *right)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = OPERATOR;
	new->value = tk->type;
	new->left = left;
	new->right = right;
	return (new);
}

t_token	*peekaboo(t_token *tk)
{
	while (tk)
	{
		if (tk->type == AND || tk->type == OR || tk->type == PARENTHESIS_L)
			return (tk);
		tk = tk->next;
	}
	return (NULL);
}

t_ast	*recursive_parse(t_token *tk)
{
	t_token *head;
	t_token	*current;
	t_token *tmp;
	t_ast	*new;

	head = tk;
	current = peekaboo(tk);
	if (current->type == PARENTHESIS_L)
	{
		current = current->next;
		recursive_parse(current);
	}
	if (is_logical_operator(current->type))
	{
		tmp = peekaboo(current->next);
		if (is_logical_operator(tmp));
			new = ast_newoperator(current, ast_newcmd(head), ast_newcmd(current->next));
	}
	else
		return (ast_newcmd(head));
}

int	parse_input(char *line)
{
	t_token *tk;

	tk =NULL;
	if (!tokenize(line, &tk))
		return (0);
	return (1);
}
