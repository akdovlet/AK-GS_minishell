/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:38:15 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/28 13:33:17 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

t_token	*token_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!*(lst))
		*lst = new;
	else
	{
		last = token_last(*lst);
		last->next = new;
		new->prev = last;
	}
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
