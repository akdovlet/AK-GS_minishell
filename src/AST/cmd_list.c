/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:22:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/24 11:29:36 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

void		cmdlst_print(t_cmdlst *lst)
{
	while (lst)
	{
		fprintf(stderr, "%s\n", lst->str);
		lst = lst->next;
	}
}

t_cmdlst	*cmdlst_last(t_cmdlst *lst)
{
	t_cmdlst	*index;

	index = lst;
	if (!lst)
		return (NULL);
	while (index->next)
		index = index->next;
	return (index);
}

void	cmdlst_add_back(t_cmdlst **lst, t_cmdlst *new)
{
	if (!*(lst))
		*lst = new;
	else
		cmdlst_last(*lst)->next = new;
}

void	cmdlst_clear(t_cmdlst **lst)
{
	t_cmdlst	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->str);
		free((*lst));
		*lst = tmp;
	}
}

t_cmdlst	*cmdlst_new(char *value, int type)
{
	t_cmdlst	*new;

	new = malloc(sizeof(t_cmdlst));
	if (!new)
		return (NULL);
	*new = (t_cmdlst){};
	new->str = ft_strdup(value);
	if (!new->str)
		return (NULL);
	new->type = type;
	return (new);
}
