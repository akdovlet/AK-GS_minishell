/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/16 19:13:31 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	dispatcher(char *line, int *i, t_token **tk)
{
	if (is_operator(line[*i]))
		if (!operator_management(line, i, tk))
			return (0);
	if (is_redirect(line[*i]))
		if (!redirect_management(line, i, tk))
			return (0);			
	if (is_parenthesis(line[*i]))
		if (!parenthesis_management(line, i, tk))
			return (0);
	if (is_word(line[*i]))
		if (!word_management(line, i, tk))
			return (0);					
	return (1);
}

int	tokenize(char *line, t_token **tk)
{
	int	i;
	int	tk_count;

	i = 0;
	tk_count = 0;
	while (line[i] && line[i] != '\n')
	{
		tk_count++;
		if (!dispatcher(line, &i, tk))
			return (token_clear(tk), 2);
		// if ((*tk) && tk_count == 1 && is_operator((*tk)->type))
		// 	return (bad_syntax((*tk)->type), token_clear(tk), 2);
		if (line[i] && is_blank(line[i]))
			i++;
	}
	if (!syntax_order_check(*tk))
	{
		printf("less efficient\n");	
		return (token_clear(tk), 2);
	}
	return (1);
}
