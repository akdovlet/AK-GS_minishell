/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:11:27 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/14 14:45:11 by gschwand         ###   ########.fr       */
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
    t_files *files;
    char *res;
    
    res = NULL;
    files = ft_recover_files();
    if (!files)
        return (NULL);
    res = sort_files(files, str);
    printf("res = %s\n", res);
    return (res);
}

int ft_wildcard(char **tab_cmd)
{
    int i;

    i = 0;
    while (tab_cmd[i])
    {
        if (ft_find_chr(tab_cmd[i], '*') != -1)
        {
            tab_cmd[i] = expand_wildcard(tab_cmd[i]);
            if (!tab_cmd[i])
                return (1);
        }
        i++;
    }
    return (0);
}
