/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/08 14:57:12 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"


// echo salut && | pwd | grep home
// WORD:echo->WORD:salut->OPERATOR:&&->OPERATOR:|
int	dispatcher(char *line, int *i, t_token **tk, t_data *data)
{
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
		if (!word_management(line, i, tk, data))
			return (1);
	return (0);
}

int	tokenize(char *line, t_token **tk, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (dispatcher(line, &i, tk, data))
			return (token_clear(tk), 2);
		if (line[i] && is_blank(line[i]))
			i++;
	}
	if (!syntax_order_check(*tk))
		return (token_clear(tk), 2);
	return (0);
}
