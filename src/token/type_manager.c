/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:01:53 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/20 17:05:18 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

char	*copy_value(char *str, int *i, bool (*f)(int))
{
	int		j;
	char	*dup;

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
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: operator_management: %s\n", strerror(errno));
		return (0);
	}
	if (str[*i] == '&')
		new->type = and_check(str, *i);
	else if (str[*i] == '|')
		new->type = or_check(str, *i);
	new->value = copy_operator(str, i, str[*i]);
	if (!new->value)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: operator_management: %s\n", strerror(errno));
		free(new);
		return (0);
	}
	if (!token_add_back_grammar(tk, new))
		return (0);
	return (1);
}

int	redirect_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = token_new(NULL);
	if (!new)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: redirect_management: %s\n", strerror(errno));
		return (0);
	}
	if (str[*i] == OUT)
		new->type = out_check(str, *i);
	else if (str[*i] == IN)
		new->type = in_check(str, *i);
	new->value = copy_operator(str, i, str[*i]);
	if (!new->value)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: redirect_management: %s\n", strerror(errno));
		free(new);
		return (0);
	}
	if (!token_add_back_grammar(tk, new))
		return (0);
	return (1);
}
