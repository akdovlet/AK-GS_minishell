/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:27:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/21 14:54:55 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_fdlst	*fdlst_new(int fd, bool close_in_child)
{
	t_fdlst	*new;

	new = malloc(sizeof(t_fdlst));
	if (!new)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: fdlst_new: %s\n", strerror(errno));
		return (NULL);
	}
	new->close_in_child = close_in_child;
	new->fd = fd;
	new->next = NULL;
	return (new);
}

int	fdlst_add_front(t_fdlst **lst, t_fdlst *new)
{
	if (!new)
		return (1);
	if (*lst)
		new->next = *lst;
	*lst = new;
	return (0);
}

void	fdlst_close_in_child(t_fdlst *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->close_in_child)
			close(lst->fd);
		lst = lst->next;
	}
}
