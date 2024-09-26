/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/24 15:32:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	dispatcher(char *line, int *i, t_token **tk, t_env *env)
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
		if (!word_management(line, i, tk, env))
			return (0);
	return (1);
}

int	tokenize(char *line, t_token **tk, t_env *env)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!dispatcher(line, &i, tk, env))
			return (token_clear(tk), 2);
		if (line[i] && is_blank(line[i]))
			i++;
	}
	if (!syntax_order_check(*tk))
		return (token_clear(tk), 2);
	return (0);
}
