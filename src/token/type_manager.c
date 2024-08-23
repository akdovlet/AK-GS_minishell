/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:01:53 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/23 17:59:21 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

char	*copy_value(char *str, int *i, bool (*f)(int))
{
	int		j;
	char	*dup;

	j = 0;
	dup = malloc(sizeof(char) * 3);
	if (!dup)
		return (NULL);
	j = 0;
	while (str[*i] && str[*i] != '\n' && f(str[*i]) && j < 2)
	{
		dup[j] = str[*i];
		j++;
		(*i)++;
	}
	dup[j] = '\0';
	return (dup);
}

char	*copy_operator(char *str, int *i, char type)
{
	int		j;
	char	*dup;

	dup = malloc(sizeof(char) * 3);
	if (!dup)
		return (NULL);
	j = 0;
	while (str[*i] && str[*i] != '\n' && str[*i] == type && j < 2)
	{
		dup[j] = str[*i];
		j++;
		(*i)++;
	}
	dup[j] = '\0';
	return (dup);
}

int	operator_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = token_new(NULL);
	if (!new)
		return (perror("malloc"), 0);
	*new = (t_token){};
	if (str[*i] == '&')
		new->type = and_check(str, *i);
	else if (str[*i] == '|')
		new->type = or_check(str, *i);
	new->value = copy_operator(str, i, str[*i]);
	if (!new->value)
		return (free(new), perror("malloc"), 0);
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
		return (bad_syntax(new->type * -1), free(new), 0);
	new->value = copy_value(str, i, is_redirect);
	if (!new->value)
		return (token_clear(tk), free(new), 0);
	token_add_back(tk, new);
	return (1);
}

