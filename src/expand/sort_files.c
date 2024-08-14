/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:22:33 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/14 10:23:06 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int ft_strcmp_start_end_wildcard(char *file, char *str)
{
    int i;

    i = 0;
    while (str[i] && file[i])
    {
        if (str[i] == '*')
            return (true);
        if (str[i] != file[i])
            return (false);
        i++;
    }
    return (true);
}

int ft_strcmp_end_start_wildcard(char *file, char *str)
{
    int i;
    int j;
    int k;

    if (!str || !file)
        return (printf("str or file is NULL\n"), false);
    i = ft_strlen(file) - 1;
    j = ft_strlen(str) - 1;
    k = 0;
    while (i - k >= 0 && j - k >= 0)
    {
        if (str[j - k] == '*')
            return (true);
        if (str[j - k] != file[i - k])
            return (false);
        k++;
    }
    return (true);
}

void ft_lstcomp_wildcard(t_files **files, char *str, int (*strcmp)(char*, char*))
{
    t_files *tmp;
    t_files *tmp2;

    tmp = *files;
    while (tmp)
    {
        if (!strcmp(tmp->name, str))
        {
            tmp2 = tmp;
            tmp = tmp->next;
            ft_lstdelone_files(files, tmp2);
        }
        else
            tmp = tmp->next;
    }
}

void ft_strlcat_files(char *dst, const char *src, size_t lenres)
{
    ft_strlcat(dst, "\"", lenres);
    ft_strlcat(dst, src, lenres);
    ft_strlcat(dst, "\"", lenres);
    ft_strlcat(dst, " ", lenres);
}


char *write_files(t_files *files)
{
    t_files *tmp;
    char *res;
    int lenres;

    tmp = files;
    lenres = 0;
    while (tmp)
    {
        lenres += ft_strlen(tmp->name) + 3;
        tmp = tmp->next;
    }
    res = ft_calloc(sizeof(char), lenres + 1);
    if (!res)
        return (perror("malloc"), NULL);
    tmp = files;
    while (tmp)
    {
        ft_strlcat_files(res, tmp->name, lenres + 1);
        tmp = tmp->next;
    }
    return (res);
}