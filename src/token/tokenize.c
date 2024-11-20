/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/20 14:34:17 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	dispatcher(char *line, int *i, t_token **tk, t_data *data)
{
	int	err;

	if (is_operator(line[*i]))
		if (!operator_management(line, i, tk))
			return (1);
	if (is_redirect(line[*i]))
		if (!redirect_management(line, i, tk))
			return (1);
	if (is_parenthesis(line[*i]))
		if (!parenthesis_management(line, i, tk))
			return (1);
	if (is_word(line[*i]))
	{
		err = word_management(line, i, tk, data);
		if (err)
			return (err);
	}
	return (0);
}

int	tokenize(char *line, t_token **tk, t_data *data)
{
	int	i;
	int	err;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		err = dispatcher(line, &i, tk, data);
		if (err)
		{
			token_clear(tk);
			return (err);
		}
		if (line[i] && is_blank(line[i]))
			i++;
	}
	if (!syntax_order_check(*tk))
		return (token_clear(tk), 2);
	return (0);
}
