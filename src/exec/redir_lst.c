/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:27:22 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/08 12:57:38 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_fdlst	*fdlst_new(int fd, bool close_in_child)
{
	t_fdlst	*new;

	new = malloc(sizeof(t_fdlst));
	if (!new)
	{
		ft_dprintf(STDERR_FILENO, "minishell: fdlst_new: %s\n", strerror(errno));
		return (NULL);
	}
	new->close_in_child = close_in_child;
	new->fd = fd;
	new->next = NULL;
	return (new);
}

t_fdlst	*fdlst_last(t_fdlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	fdlst_add_back(t_fdlst	**lst, t_fdlst *new)
{
	if (!*lst)
		*lst = new;
	else
		fdlst_last(*lst)->next = new;
}

void	fdlst_close_in_child(t_fdlst **lst)
{
	if (!*lst || !lst)
		return ;
	while (*lst)
	{
		if ((*lst)->close_in_child)
			close((*lst)->fd);
		fdlst_eat(lst);
	}
	*lst = NULL;
}
