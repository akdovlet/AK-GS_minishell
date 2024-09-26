/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:06:38 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/26 11:41:27 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	ft_new_lst_add_back_files(t_files **alst, t_files *new)
{
	t_files	*tmp;

	if (!new)
		return (1);
	if (!*alst)
	{
		*alst = new;
		return (0);
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

void	ft_lst_add_back_files(t_files **alst, t_files *new)
{
	t_files	*tmp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_files *ft_lstnew_files(char *str)
{
    t_files *new;

    new = malloc(sizeof(t_files));
    if (!new)
    {
        perror("malloc");
        return (NULL);
    }
    new->name = str;
    new->next = NULL;
    return (new);
}

t_files *ft_lstnew_files_dup(char *str)
{
    t_files *new;

    new = malloc(sizeof(t_files));
    if (!new)
    {
        perror("malloc");
        return (NULL);
    }
    new->name = ft_strdup(str);
    if (!new->name)
    {
        perror("malloc");
        free(new);
        return (NULL);
    }
    new->next = NULL;
    return (new);
}

void ft_lstdelone_files(t_files **files, t_files *to_delete)
{
	t_files	*tmp;

	if (*files == to_delete)
	{
		*files = (*files)->next;
		free(to_delete->name);
		free(to_delete);
		return ;
	}
	tmp = *files;
	while (tmp && tmp->next != to_delete)
		tmp = tmp->next;
	if (tmp && tmp->next == to_delete)
	{
		tmp->next = to_delete->next;
		free(to_delete->name);
		free(to_delete);
	}
}
