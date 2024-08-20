/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pidlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:18:30 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/20 17:10:21 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_pidlst	*ft_lstnew_pidlst(pid_t pid)
{
    t_pidlst *new;
    
    new = malloc(sizeof(t_pidlst));
    if (!new)
        return (perror("malloc failed\n"), NULL);
    new->next = NULL;
    new->pid = pid;
    return (new);
}

void	ft_lstadd_back_pidlst(t_pidlst **lst, t_pidlst *new)
{
    t_pidlst *tmp;

    if (!*lst)
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
