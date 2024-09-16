/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:11:43 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/16 19:12:03 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	redir_rules(t_token *tk)
{
	if (!tk->next)
		return (bad_syntax3(tk->next), 0);
	if (is_redirect(tk->type) && tk->next->type != WORD)
		return (bad_syntax3(tk->next), 0);
	return (1);
}

int	operator_rules(t_token *tk)
{
	if (!tk->next)
		return (bad_syntax3(tk), 0);
	if (tk->type == BACKGROUND)
		return (bad_syntax3(tk), 0);
	if (is_operator(tk->type) && is_operator(tk->next->type))
		return (bad_syntax3(tk->next), 0);
	if (is_operator(tk->type) && tk->next->type == PARENTHESIS_R)
		return (bad_syntax3(tk->next), 0);
	return (1);
}

int	parenthesis_rules(t_token *tk)
{
	if (!tk->next)
		return (1);
	if (tk->type == PARENTHESIS_L && is_operator(tk->next->type))
		return (bad_syntax3(tk->next), 0);
	if (tk->type == WORD && tk->next->type == PARENTHESIS_L)
		return (bad_syntax3(tk->next), 0);
	if (tk->type == PARENTHESIS_L && tk->next->type == PARENTHESIS_R)
		return (bad_syntax3(tk->next), 0);
	if (tk->type == PARENTHESIS_R && tk->next->type == PARENTHESIS_L)
		return (bad_syntax3(tk->next), 0);
	return (1);
}

int	grammar_check(t_token *tk)
{
	if (!tk)
		return (1);
	if (is_operator(tk->type))
		if (!operator_rules(tk))
			return (0);
	if (is_redirect(tk->type))
		if (!redir_rules(tk))
			return (0);
	if (is_parenthesis(tk->type) || tk->type == WORD)
		if (!parenthesis_rules(tk))
			return (0);
	return (1);
}
