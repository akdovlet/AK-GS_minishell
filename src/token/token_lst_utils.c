/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:38:15 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/12 22:53:43 by akdovlet         ###   ########.fr       */
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

int	token_add_back_grammar(t_token **lst, t_token *new)
{
	t_token	*last;

	last = NULL;
	if (!*(lst))
	{
		*lst = new;
		new->prev = last;
	}
	else
	{
		last = token_last(*lst);
		last->next = new;
		new->prev = last;
		if (!grammar_check(last))
			return (0);
	}
	return (1);
}

t_token	*token_new(char *var)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	*node = (t_token){};
	node->value = var;
	node->fd = -1;
	return (node);
}

void	token_clear(t_token **tk)
{
	t_token	*tmp;

	while (*tk)
	{
		tmp = (*tk)->next;
		if ((*tk)->fd != -1)
			close ((*tk)->fd);
		free((*tk)->value);
		free((*tk));
		*tk = tmp;
	}
}
