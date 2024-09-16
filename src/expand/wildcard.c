/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:11:27 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/16 12:49:26 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

t_files *sort_files(t_files *files, char *str)
{
    t_files *tmp;

    // ft_print_lst_files(files);
    ft_lstcomp_wildcard(&files, str);\
    printf("____________________\n");
    // ft_print_lst_files(files);
    if (!files)
    {
        tmp = ft_lstnew_files(str);
        if (!files)
            return (NULL);
        files = tmp;
    }
    return (files);
}

t_files  *expand_wildcard(t_files **files, char *str)
{
    t_files *files_tmp;
    
    printf("expand_wildcard\n");
    files_tmp = ft_recover_files();
    if (!files_tmp)
        return (ft_free_lst_files(files), NULL);
    files_tmp = sort_files(files_tmp, str);
    printf("files_tmp\n");
    ft_print_lst_files(files_tmp);
    ft_lst_add_back_files(files, files_tmp);
    // ft_print_lst_files(*files);
    return (*files);
}

// fonction qui va revoyer un tableau de char * avec les noms des fichiers
// qui correspondent a la wildcard
char **ft_files_to_tab(t_files *files)
{
    char **tab;
    t_files *tmp;
    int i;

    i = 0;
    tmp = files;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    tab = malloc(sizeof(char *) * (i + 1));
    if (!tab)
        return (NULL);
    i = 0;
    tmp = files;
    while (tmp)
    {
        tab[i] = tmp->name;
        tmp = tmp->next;
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

char **ft_wildcard(char **tab_cmd)
{
    t_files *files;
    t_files *tmp;
    int i;

    files = NULL;
    i = 0;
    // print_tab(tab_cmd);
    while (tab_cmd[i])
    {
        if (ft_find_chr(tab_cmd[i], '*'))
            files = expand_wildcard(&files, tab_cmd[i]);
        else
        {
            tmp = ft_lstnew_files(tab_cmd[i]);
            if (!tmp)
                return (NULL);
            ft_lst_add_back_files(&files, tmp);
        }
        i++;
    }
    ft_free_tab(tab_cmd);
    tab_cmd = ft_files_to_tab(files);
    // print_tab(tab_cmd);
    if (!tab_cmd)
        return (NULL);
    return (tab_cmd);
}
