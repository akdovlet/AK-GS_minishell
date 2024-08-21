/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:01:53 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/21 17:33:24 by akdovlet         ###   ########.fr       */
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
	while (str[*i] && str[*i] != '\n' && f(str[*i]))
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

	new = token_new(NULL);
	if (!new)
		return (perror("malloc"), 0);
	if (str[*i] == '&')
		new->type = and_check(str, *i);
	else if (str[*i] == '|')
		new->type = or_check(str, *i);
	if (new->type <= 0)
		return (bad_syntax(new->type * -1), 0);
	new->value = copy_value(str, i, is_operator);
	if (!new->value)
		return (perror("malloc"), 0);
	token_add_back(tk, new);
	return (1);
}

int	redirect_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = token_new(NULL);
	if (!new)
		return (token_clear(tk), 0);
	if (str[*i] == OUT)
		new->type = out_check(str, *i);
	else if (str[*i] == IN)
		new->type = in_check(str, *i);
	if (new->type < 0)
		return (bad_syntax(new->type * -1), 0);
	new->value = copy_value(str, i, is_redirect);
	if (!new->value)
		return (token_clear(tk), 0);
	token_add_back(tk, new);
	return (1);
}

