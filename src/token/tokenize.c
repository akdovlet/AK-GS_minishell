/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/22 16:12:04 by akdovlet         ###   ########.fr       */
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

int	tokenize(char *line, t_token **tk)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!dispatcher(line, &i, tk))
			return (token_clear(tk), 0);
		else if (line[i] && is_blank(line[i]))
			i++;
	}
	if (!syntax_order_check(*tk) || !parenthesis_count(line, 0))
		return (token_clear(tk), 0);
	return (1);
}
