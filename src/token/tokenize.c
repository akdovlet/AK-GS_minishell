/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/15 11:35:38 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	tokenize(char *line, t_token **tk)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (is_operator(line[i]))
		{
			if (!opperator_management(line, &i, tk))
				return (ft_tkclear(tk), 0);			
		}
		if (is_redirect(line[i]))
		{
			if (!redirect_management(line, &i, tk))
				return (ft_tkclear(tk), 0);			
		}
		if (is_parenthesis(line[i]))
		{
			if (!parenthesis_management(line, &i, tk))
				return (ft_tkclear(tk), 0);
		}
		if (line[i] && !ft_isspace(line[i]))
		{
			if (!word_management(line, &i, tk))
				return (ft_tkclear(tk), 0);					
		}
		else if (line[i])
			i++;
	}
	if (!syntax_order_check(*tk) || !parenthesis_count(line, 0))
		return (ft_tkclear(tk), 0);
	return (1);
}
