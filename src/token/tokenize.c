/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/12 18:11:42 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void	print_token(t_token *tk)
{
	while (tk)
	{
		ft_printf("type is: %d\t", tk->type);
		ft_printf("value is: %s\n", tk->value);
		tk = tk->next;
	}
}

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
	if (!syntax_order_check(*tk))
		return (ft_tkclear(tk), 0);
	return (1);
}
