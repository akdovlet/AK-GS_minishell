/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:01:53 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/10 15:17:22 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

char	*copy_value(char *str, int *i, bool (*f)(int))
{
	int		j;
	char	*dup;

	j = 0;
	while (str[*i + j] && f(str[*i + j]))
		j++;
	dup = malloc(sizeof(char) * j + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (str[*i] && f(str[*i]))
	{
		dup[j] = str[*i];
		j++;
		(*i)++;
	}
	dup[j] = '\0';
	return (dup);
}

int	opperator_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = ft_tokennew(NULL);
	if (!new)
		return (0);
	if (str[*i] + str[*i + 1] == AND)
	{
		new->type = AND;
		if (is_operator(str[*i + 2]))
		{
			bad_syntax(AND);
			ft_tkclear(tk);
			return (0);
		}
	}
	else if (str[*i] + str[*i + 1] == OR)
		new->type = OR;
	else if (str[*i] == PIPE)
		new->type = PIPE;
	new->value = copy_value(str, i, is_operator);
	if (!new->value)
		return (0);
	ft_token_add_back(tk, new);
	return (1);
}

void	redirect_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = ft_tokennew(NULL);
	if (!new)
		return ;
	if (str[*i] + str[*i + 1] == APPEND)
		new->type = APPEND;
	else if (str[*i] + str[*i + 1] == HERE_DOC)
		new->type = HERE_DOC;
	else if (str[*i] == IN)
		new->type = IN;
	else if (str[*i] == OUT)
		new->type = OUT;
	new->value = copy_value(str, i, is_redirect);
	if (!new->value)
		return ;
	ft_token_add_back(tk, new);
}

