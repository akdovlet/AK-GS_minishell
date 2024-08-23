/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:53:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/23 15:42:07 by akdovlet         ###   ########.fr       */
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
		return (perror("malloc"), 0);
	new->type = str[*i];
	if (!new->type)
		return (free(new), 0);
	new->value = copy_parenthesis(str, i);
	if (!new->value)
		return (free(new), perror("malloc"), 0);
	token_add_back(tk, new);
	return (1);
}
