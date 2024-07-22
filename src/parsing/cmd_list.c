/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:22:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/20 20:29:22 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_cmdlist	*cmdlst_last(t_cmdlist *lst)
{
	t_token	*index;

	index = lst;
	if (!lst)
		return (NULL);
	while (index->next)
		index = index->next;
	return (index);
}

void	cmdlst_add_back(t_cmdlist **lst, t_cmdlist *new)
{
	if (!*(lst))
		*lst = new;
	else
		cmdlst_last(*lst)->next = new;
}

void	cmdlst_clear(t_cmdlist **lst)
{
	t_cmdlist	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_free((*lst)->cmd);
		free((*lst));
		*lst = tmp;
	}
}

t_cmdlist	*new_cmdnode(void)
{
	t_cmdlist	*new;

	new = malloc(sizeof(t_cmdlist));
	if (!new)
		return (NULL);
	*new = (t_cmdlist){};
}
