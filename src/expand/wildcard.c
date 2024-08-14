/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:11:27 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/14 10:23:20 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char *sort_files(t_files *files, char *str)
{
    char *res;

    ft_lstcomp_wildcard(&files, str, ft_strcmp_start_end_wildcard);
    ft_lstcomp_wildcard(&files, str, ft_strcmp_end_start_wildcard);
    res = write_files(files);
    ft_free_lst_files(files);
    return (res);
}

// remove the first two files
// funct need to be retry
void ft_supp_point_files(t_files **files)
{
    t_files *tmp;
    
    tmp = *files;
    *files = (*files) -> next;
    free((*files)->name);
    free(tmp);
    tmp = *files;
    *files = (*files) -> next;
    free((*files)->name);
    free(tmp);
}

// res will return all the files who correspond to the wildcard
char  *expand_wildcard(char *str)
{
    t_files *files;
    char *res;
    
    res = NULL;
    files = ft_recover_files();
    if (!files)
        return (NULL);
    // ft_supp_point_files(&files);
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
