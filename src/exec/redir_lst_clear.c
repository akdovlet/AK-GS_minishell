/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:01:24 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/09 17:53:28 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	fdlst_dont_close_in_child(t_fdlst *lst, int fd_target)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->fd == fd_target)
		{
			lst->close_in_child = false;
			break ;
		}
		lst = lst->next;
	}
}

void	fdlst_eat(t_fdlst **node)
{
	t_fdlst	*tmp;

	if (!(*node) || !node)
		return ;
	tmp = (*node)->next;
	free(*node);
	*node = tmp;
}

void	fdlst_delete_node(t_fdlst **lst, int key)
{
	t_fdlst	*head;
	t_fdlst	*previous;

	head = *lst;
	previous = *lst;
	if (head && head->fd == key)
	{
		head = (*lst)->next;
		free(*lst);
		*lst = head;
		return ;
	}
	while (head && head->fd != key)
	{
		previous = head;
		head = head->next;
	}
	if (head == NULL)
		return ;
	previous->next = head->next;
	free(head);
}

void	fdlst_clear(t_fdlst **lst)
{
	if (!lst || !*lst)
		return ;
	while (*lst)
		fdlst_eat(lst);
	*lst = NULL;
}
