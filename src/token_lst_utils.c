/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:38:15 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/04 13:50:48 by akdovlet         ###   ########.fr       */
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

void	ft_add_back(t_token **lst, t_token *new)
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
