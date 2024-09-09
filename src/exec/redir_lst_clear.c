/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:01:24 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/08 12:51:37 by akdovlet         ###   ########.fr       */
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

void	fdlst_clear(t_fdlst **lst)
{
	if (!lst || !*lst)
		return ;
	while (*lst)
		fdlst_eat(lst);
	*lst = NULL;
}
