/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:46:28 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/23 17:30:41 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	check_token(t_token *tk)
{
	if (!tk->next)
	{
		if (is_redirect(tk->type) || is_operator(tk->type))
			return (bad_syntax3(tk->next), 0);
		return (1);
	}
	if (tk->type == BACKGROUND)
		return (bad_syntax3(tk), 0);
	if (is_operator(tk->type) && is_operator(tk->next->type))
		return (bad_syntax3(tk->next), 0);
	if (is_operator(tk->type) && tk->next->type == PARENTHESIS_R)
		return (bad_syntax3(tk->next), 0);
	if (is_redirect(tk->type) && tk->next->type != WORD)
		return (bad_syntax3(tk->next), 0);
	if (tk->type == PARENTHESIS_L && is_operator(tk->next->type))
		return (bad_syntax3(tk->next), 0);
	if (is_word(tk->type) && tk->next->type == PARENTHESIS_L)
		return (fprintf(stderr, "curr token is: %s\n8\n", tk->value), bad_syntax3(tk->next), 0);
	if (tk->type == PARENTHESIS_L && tk->next->type == PARENTHESIS_R)
		return (bad_syntax3(tk->next), 0);
	if (tk->type == PARENTHESIS_R && tk->next->type == PARENTHESIS_L)
		return (bad_syntax3(tk->next), 0);
	return (1);
}

int	scope_recursive(t_token **tk)
{
	int	error;

	while (*tk)
	{
		if (!check_token(*tk))
			return (3);
		if ((*tk)->type == PARENTHESIS_L)
		{
			*tk = (*tk)->next;
			error = scope_recursive(tk);
			if (error == 1)
				return (1);
		}
		else if ((*tk)->type == PARENTHESIS_R)
		{
			(*tk) = (*tk)->next;
			return (0);
		}
		else 
			*tk = (*tk)->next;
	}
	return (1);
}

int	subshell_rule(t_token **tk)
{
	if (!*tk || (*tk)->type == PARENTHESIS_R)
		return (0);
	while (*tk && (*tk)->type != PARENTHESIS_R && !is_operator((*tk)->type))
	{
		if (!check_token(*tk))
			return (3);
		if (is_redirect((*tk)->type))
			*tk = (*tk)->next->next;
		else if ((*tk)->type == WORD)
			return (bad_syntax3(*tk), 3);
		else
			(*tk) = (*tk)->next;
	}
	return (0);
}

int	scope_check(t_token **tk)
{
	int error;
	
	error = 0;
	if (!(*tk) || !tk)
		return (1);
	while (*tk)
	{
		if (!check_token(*tk))
			return (3);
		if ((*tk)->type == PARENTHESIS_L)
		{
			*tk = (*tk)->next;
			error = scope_recursive(tk);
			if (error)
				return (error);
			if (subshell_rule(tk))
				return (3);
		}
		else if ((*tk)->type == PARENTHESIS_R)
			return (bad_syntax(PARENTHESIS_R), 2);
		else
			*tk = (*tk)->next;
	}
	return (error);
}

int	syntax_order_check(t_token *tk)
{
	int	error;

	if (!tk)
		return (1);
	if (is_operator(tk->type))
		return (bad_syntax(tk->type), 0);
	while (tk)
	{
		if (!check_token(tk))
			return (0);
		if (tk->type == PARENTHESIS_L)
		{
			error = scope_check(&tk);
			if (error == 1)
				return (ft_dprintf(STDERR_FILENO, PARENTHESIS_ERR, PARENTHESIS_R), 0);
			if (error == 2 || error == 3)
				return (0);
		}
		else if (tk->type == PARENTHESIS_R)
			return (bad_syntax(PARENTHESIS_R), 0);
		else
			tk = tk->next;
	}
	return (1);
}
