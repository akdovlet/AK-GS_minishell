/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/22 12:28:38 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	dispatcher(char *line, int *i, t_token **tk)
{
	if (is_operator(line[*i]))
	{
		if (!opperator_management(line, i, tk))
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

int	find_operator(t_token *tk)
{
	while (tk && tk->type != PARENTHESIS_L && tk->type != PARENTHESIS_R)
	{
		if (is_logical_operator(tk->type))
			return (1);
		tk = tk->next;
	}
	return (0);
}

// remove useless parenthesis
// void	redundant_parenthesis(t_token **tk)
// {
// 	t_token	*cursor;
// 	t_token	*prev;

// 	cursor = *tk;
// 	while (cursor)
// 	{
// 		prev = cursor;
// 		if (is_parenthesis(cursor->type))
// 		{
// 			if (!find_operator(cursor->next))
// 				delete_node(&cursor, &prev);
// 			else
// 				cursor = cursor->next;
// 		}
// 		else
// 			cursor = cursor->next;
// 	}
// }

int	tokenize(char *line, t_token **tk)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!dispatcher(line, &i, tk))
		{
			return (ft_tkclear(tk), 0);
		}
		else if (line[i] && is_blank(line[i]))
			i++;
	}
	if (!syntax_order_check(*tk) || !parenthesis_count(line, 0))
		return (ft_tkclear(tk), 0);
	// redundant_parenthesis(&tk);
	return (1);
}
