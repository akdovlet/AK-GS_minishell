/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:01:53 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/11 15:45:06 by akdovlet         ###   ########.fr       */
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
	ft_token_add_back(tk, new);
	return (1);
}

//finish redir checks
// int	redirect_check(char *str, int i)
// {
// 	if (str[i] + str[i + 1] == APPEND)
		
// }

int	redirect_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = ft_tokennew(NULL);
	if (!new)
		return (ft_tkclear(tk), 0);
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
		return (ft_tkclear(tk), 0);
	ft_token_add_back(tk, new);
	return (1);
}

