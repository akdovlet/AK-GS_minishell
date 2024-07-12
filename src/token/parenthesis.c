/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:53:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/12 18:04:37 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	parenthesis_check(int symbol, char *str, int *i)
{
	if (symbol == '(' && str[*i + 1] == ')')
	{
		ft_dprintf(STDERR_FILENO, PARENTHESIS_ERR, symbol);
		return (0);
	}
	if (symbol == ')' && str[*i + 1] == '(')
	{
		ft_dprintf(STDERR_FILENO, PARENTHESIS_ERR, symbol);
		return (0);
	}
	return (symbol);
}

char	*copy_parenthesis(char *str, int *i)
{
	char	*dup;

	dup = malloc(sizeof(char) * 2);
	if (!dup)
		return (NULL);	
	dup[0] = str[(*i)++];
	dup[1] = '\0';
	return (dup);
}

int	find_parenthesis(char *str, int i)
{
	
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ')')
			return (1);
		i++;
	}
	return (0);
}

int	parenthesis_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	if (str[*i] == '(')
	{
		if (!find_parenthesis(str, *i))
		{
			ft_dprintf(STDERR_FILENO, PARENTHESIS_ERR, ')');
			return (0);
		}		
	}
	new = ft_tokennew(NULL);
	if (!new)
		return (perror("malloc"), 0);
	new->type = parenthesis_check(str[*i], str, i);
	if (!new->type)
		return (free(new), 0);
	new->value = copy_parenthesis(str, i);
	if (!new->value)
		return (free(new), ft_tkclear(tk), 0);
	ft_token_add_back(tk, new);
	return (1);
}
