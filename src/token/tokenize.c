/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/11 15:33:50 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void	print_token(t_token *tk)
{
	while (tk)
	{
		ft_printf("||type is: %d\t", tk->type);
		ft_printf("value is: %s |->\n", tk->value);
		tk = tk->next;
	}
	ft_printf("||NULL\n");
}

// can shorten with one dispatch function
void	tokenize(char *line)
{
	int		i;
	t_token	*tk;

	i = 0;
	tk = NULL;
	while (line[i] && line[i] != '\n')
	{
		if (is_operator(line[i]))
		{
			if (!opperator_management(line, &i, &tk))
				return (ft_tkclear(&tk));			
		}
		else if (is_redirect(line[i]))
		{
			if (!redirect_management(line, &i, &tk))
				return (ft_tkclear(&tk));
		}
		else if (!ft_isspace(line[i]))
		{
			if (!word_management(line, &i, &tk))
				return (ft_tkclear(&tk));			
		}
		else
			i++;
	}
	print_token(tk);
	ft_tkclear(&tk);
}
