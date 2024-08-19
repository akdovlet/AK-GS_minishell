/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:22:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/19 17:19:40 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

void		cmdlst_print(t_cmdlist *lst)
{
	while (lst)
	{
		fprintf(stderr, "%s\n", lst->str);
		lst = lst->next;
	}
}

t_cmdlist	*cmdlst_last(t_cmdlist *lst)
{
	t_cmdlist	*index;

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
		free((*lst)->str);
		free((*lst));
		*lst = tmp;
	}
}

t_cmdlist	*cmdlst_new(char *value, int type)
{
	t_cmdlist	*new;

	new = malloc(sizeof(t_cmdlist));
	if (!new)
		return (NULL);
	*new = (t_cmdlist){};
	new->str = ft_strdup(value);
	if (!new->str)
		return (NULL);
	new->type = type;
	return (new);
}
