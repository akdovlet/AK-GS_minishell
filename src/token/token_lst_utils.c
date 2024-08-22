/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:38:15 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/21 17:33:24 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

t_token	*token_last(t_token *lst)
{
	t_token	*index;

	index = lst;
	if (!lst)
		return (NULL);
	while (index->next)
		index = index->next;
	return (index);
}

void	token_add_back(t_token **lst, t_token *new)
{
	if (!*(lst))
		*lst = new;
	else
		token_last(*lst)->next = new;
}

t_token	*token_new(char *var)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	*node = (t_token){};
	node->value = var;
	return (node);
}

void	token_clear(t_token **tk)
{
	t_token	*tmp;

	while (*tk)
	{
		tmp = (*tk)->next;
		free((*tk)->value);
		free((*tk));
		*tk = tmp;
	}
}
