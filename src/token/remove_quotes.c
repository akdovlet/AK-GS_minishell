/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 20:36:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/12 18:58:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	redir_quote_len(char *str, int *i, int symbol)
{
	int	len;

	len = 0;
	(*i)++;
	while (str[*i] && str[*i] != symbol)
	{
		len++;
		(*i)++;
	}
	if (str[*i] == symbol)
		(*i)++;
	return (len);
}

int	redir_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] && is_quote(str[i]))
			len += redir_quote_len(str, &i, str[i]);
		else if (str[i])
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	redir_quote_manager(char *dup, char *str, int *i, int *j)
{
	int	symbol;

	symbol = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != symbol)
	{
		dup[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	if (str[*i] == symbol)
		(*i)++;
}

char	*remove_quotes(char *str)
{
	char	*dup;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (redir_len(str) + 1));
	if (!dup)
		return (NULL);
	while (str[i])
	{
		if (str[i] && is_quote(str[i]))
			redir_quote_manager(dup, str, &i, &j);
		else
			dup[j++] = str[i++];
	}
	dup[j] = '\0';
	return (dup);
}
