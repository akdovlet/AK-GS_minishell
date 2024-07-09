/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:38:15 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/09 15:14:32 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

t_token	*ft_tokenlast(t_token *lst)
{
	t_token	*index;

	index = lst;
	if (!lst)
		return (NULL);
	while (index->next)
		index = index->next;
	return (index);
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	if (!*(lst))
		*lst = new;
	else
		ft_tokenlast(*lst)->next = new;
}

t_token	*ft_tokennew(char *var)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	*node = (t_token){};
	node->value = var;
	return (node);
}

void	ft_tkclear(t_token **tk)
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
