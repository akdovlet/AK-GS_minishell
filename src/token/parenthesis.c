/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:53:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/21 17:33:09 by akdovlet         ###   ########.fr       */
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

int	parenthesis_count(char *str, int i)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == PARENTHESIS_L)
			left++;
		if (str[i] == PARENTHESIS_R)
			right++;
		i++;
	}
	if (left > right)
	{
		ft_dprintf(STDERR_FILENO, PARENTHESIS_ERR, ')');
		return (0);	
	}
	else if (left < right)
	{
		bad_syntax(PARENTHESIS_R);
		return (0);	
	}
	return (1);
}

int	parenthesis_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = token_new(NULL);
	if (!new)
		return (perror("malloc"), 0);
	new->type = parenthesis_check(str[*i], str, i);
	if (!new->type)
		return (free(new), 0);
	new->value = copy_parenthesis(str, i);
	if (!new->value)
		return (free(new), perror("malloc"), 0);
	token_add_back(tk, new);
	return (1);
}
