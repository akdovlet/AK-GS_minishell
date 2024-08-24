/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/24 11:53:50 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	dispatcher(char *line, int *i, t_token **tk)
{
	if (is_operator(line[*i]))
	{
		if (!operator_management(line, i, tk))
			return (0);			
	}
	if (is_redirect(line[*i]))
	{
		if (!redirect_management(line, i, tk))
			return (0);			
	}
	if (is_parenthesis(line[*i]))
	{
		if (!parenthesis_management(line, i, tk))
			return (0);
	}
	if (is_word(line[*i]))
	{
		if (!word_management(line, i, tk))
			return (0);					
	}
	return (1);
}

int	grammar_check(t_token *tk)
{
	if (!tk)
		return (1);
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
		return (bad_syntax3(tk->next), 0);
	if (tk->type == PARENTHESIS_L && tk->next->type == PARENTHESIS_R)
		return (bad_syntax3(tk->next), 0);
	if (tk->type == PARENTHESIS_R && tk->next->type == PARENTHESIS_L)
		return (bad_syntax3(tk->next), 0);
	return (1);
}

int	tokenize(char *line, t_token **tk)
{
	int		i;
	int		tk_count;
	t_token	*previous;

	i = 0;
	tk_count = 0;
	previous = *tk;
	while (line[i] && line[i] != '\n')
	{
		previous = *tk;
		tk_count++;
		if (!dispatcher(line, &i, tk))
			return (token_clear(tk), 0);
		else if (tk_count == 1 && is_operator((*tk)->type))
			return (bad_syntax((*tk)->type), token_clear(tk), 0);
		else if (line[i] && is_blank(line[i]))
			i++;
		if (!grammar_check(previous))
			return (token_clear(tk), 0);
	}
	if (!syntax_order_check(*tk))
		return (token_clear(tk), 0);
	return (1);
}
