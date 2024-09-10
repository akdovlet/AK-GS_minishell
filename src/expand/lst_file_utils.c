/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:06:38 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/04 18:22:29 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void ft_lst_add_back_files(t_files **alst, t_files *new)
{
    t_files *tmp;

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
    new->name = ft_strdup(str);
    new->next = NULL;
    return (new);
}

void ft_lstdelone_files(t_files **files, t_files *to_delete)
{
    t_files *tmp;

    if (*files == to_delete)
    {
        *files = (*files)->next;
        free(to_delete->name);
        free(to_delete);
        return;
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

void ft_free_lst_files(t_files **files)
{
    t_files *tmp;

    while (files)
    {
        tmp = *files;
        *files = (*files)->next;
        free(tmp);
    }
}

t_files *ft_recover_files(void)
{
    DIR *dir;
    struct dirent *entry;
    t_files *files;
    t_files *tmp;

    files = NULL;
    dir = opendir(".");
    if (dir == NULL)
    {
        perror("opendir");
        return (NULL);
    }
    while ((entry = readdir(dir)) != NULL)
    {
        tmp = ft_lstnew_files(entry->d_name);
        if (!tmp)
        {
            perror("malloc");
            return (NULL);
        }
        ft_lst_add_back_files(&files, tmp);
    }
    closedir(dir);
    return (files);
}