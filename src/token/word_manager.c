/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:04:34 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/25 16:57:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	quote_len(char *str, int *i, int symbol)
{
	int	len;

	len = 1;
	(*i)++;
	while (str[*i] && str[*i] != '\n' && str[*i] != symbol)
	{
		len++;
		(*i)++;
	}
	return (len);
}

int	quote_management(char *dup, int *j, char *str, int *i)
{
	char	symbol;

	symbol = str[*i];
	dup[(*j)++] = str[(*i)++];
	while (str[*i] && str[*i] != '\n' && str[*i] != symbol)
	{
		dup[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
	if (str[*i] != symbol)
	{
		ft_dprintf(STDERR_FILENO, NEWLINE_ERR, symbol);
		return (0);
	}
	dup[(*j)++] = str[(*i)++];
	return (1);
}

int	word_len(char *str, int *i)
{
	int	len;
	int	index;

	len = 0;
	index = *i;
	while (str[index] && str[index] != '\n')
	{
		if (is_quote(str[index]))
		{
			len += quote_len(str, &index, str[index]);
		}
		if (!is_word(str[index]))
			break ;
		else
		{
			(index)++;
			len++;
		}
	}
	return (len);
}

char	*copy_word(char *str, int *i)
{
	int		j;
	char	*dup;

	j = word_len(str, i);
	dup = malloc(sizeof(char) * j + 1);
	if (!dup)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: word_management: %s\n", strerror(errno));
		return (NULL);
	}
	j = 0;
	while (str[*i] && str[*i] != '\n' && is_word(str[*i]))
	{
		if (is_quote(str[*i]))
		{
			if (!quote_management(dup, &j, str, i))
				return (free(dup), NULL);
		}
		else
			dup[j++] = str[(*i)++];
	}
	dup[j] = '\0';
	return (dup);
}

int	word_management(char *line, int *i, t_token **tk, t_env *env)
{
	t_token	*new;

	new = token_new(NULL);
	if (!new)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: word_management: %s\n", strerror(errno));
		return (0);
	}
	new->type = WORD;
	new->value = copy_word(line, i);
	if (!new->value)
	{
		free(new);
		return (0);
	}
	if (!token_add_back_grammar(tk, new))
		return (0);
	if (new->prev && new->prev->type == HERE_DOC)
		if (!here_doc_manager(new, env))
			return (0);
	return (1);
}
