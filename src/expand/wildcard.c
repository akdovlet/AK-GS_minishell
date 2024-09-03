/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:11:27 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/03 10:28:42 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char *sort_files(t_files *files, char *str)
{
    char *res;

    ft_lstcomp_wildcard(&files, str);
    if (!files)
        res = str;
    else
        res = write_files(files);
    ft_free_lst_files(files);
    return (res);
}

char  *expand_wildcard(char *str)
{
    printf("expand_wildcard\n");
    t_files *files;
    char *res;
    
    res = NULL;
    files = ft_recover_files();
    if (!files)
        return (NULL);
    res = sort_files(files, str);
    return (res);
}

int ft_wildcard(char **tab_cmd)
{
    int i;

    i = 0;
    while (tab_cmd[i])
    {
        if (ft_find_chr(tab_cmd[i], '*'))
        {
            printf("--- on est la ---\n");
            tab_cmd[i] = expand_wildcard(tab_cmd[i]);
            if (!tab_cmd[i])
                return (1);
        }
        i++;
    }
    return (0);
}
