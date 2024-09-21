/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:53:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/21 13:13:11 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

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

int	parenthesis_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = token_new(NULL);
	if (!new)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: parenthesis_management: %s\n", strerror(errno));
		return (0);
	}
	new->type = str[*i];
	new->value = copy_parenthesis(str, i);
	if (!new->value)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: parenthesis_management: %s\n", strerror(errno));
		free(new);
		return (0);
	}
	if (!token_add_back_grammar(tk, new))
		return (0);
	return (1);
}
