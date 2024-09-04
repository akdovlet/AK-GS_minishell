/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:11:27 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/04 18:47:44 by gschwand         ###   ########.fr       */
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

    ft_lstcomp_wildcard(&files, str);
    if (!files)
    {
        tmp = ft_lstnew_files(str);
        if (!files)
            return (NULL);
        files = tmp;
    }
    return (files);
}

static char  *expand_wildcard(t_files **files, char *str)
{
    t_files *files_tmp;
    char *res;
    
    res = NULL;
    printf("ok3\n");
    files_tmp = ft_recover_files();
    printf("ok2\n");
    if (!files_tmp)
        return (ft_free_lst_files(files), NULL);
    files_tmp = sort_files(files_tmp, str);
    ft_lst_add_back_files(files, files_tmp);
    return (res);
}

// fonction qui va revoyer un tableau de char * avec les noms des fichiers
// qui correspondent a la wildcard
char **ft_files_to_tab(t_files *files)
{
    char **tab;
    int i;
    int len;

    i = 0;
    len = 0;
    while (files)
    {
        len++;
        files = files->next;
    }
    tab = malloc(sizeof(char *) * (len + 1));
    if (!tab)
        return (NULL);
    while (files)
    {
        tab[i] = files->name;
        files = files->next;
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

char **ft_wildcard(char **tab_cmd)
{
    t_files *files;
    int i;

    printf("ft_wildcard\n");
    i = 0;
    while (tab_cmd[i])
    {
        printf("tab_cmd[%d] = %s\n", i, tab_cmd[i]);
        printf("allez batard\n");
        if (ft_find_chr(tab_cmd[i], '*'))
        {
            printf("baard?\n");
            expand_wildcard(&files, tab_cmd[i]);
            if (!tab_cmd[i])
                return (NULL);
        }
        i++;
    }
    ft_print_lst_files(files);
    ft_free_tab(tab_cmd);
    tab_cmd = ft_files_to_tab(files);
    return (tab_cmd);
}
