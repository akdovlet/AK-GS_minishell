/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:42:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/21 16:09:19 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

t_ast	*redir_last(t_ast *lst)
{
	t_ast	*index;

	index = lst;
	if (!lst)
		return (NULL);
	while (index->redir_next)
		index = index->redir_next;
	return (index);
}

void	redir_add_back(t_ast **lst, t_ast *new)
{
	if (!*(lst))
		*lst = new;
	else
		redir_last(*lst)->redir_next = new;
}

void	redir_clear(t_ast **lst)
{
	t_ast	*tmp;

	while (*lst)
	{
		tmp = (*lst)->redir_next;
		free((*lst)->redir_filename);
		free((*lst));
		*lst = tmp;
	}
}
