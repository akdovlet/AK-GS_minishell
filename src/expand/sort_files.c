/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:22:33 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/14 14:45:26 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int ft_strcmp_end_start_wildcard(char *file, char *str)
{
    int i;
    int j;
    int k;

    if (!file)
        return (false);
    if (!str[0])
        return (true);
    i = ft_strlen(file) - 1;
    j = ft_strlen(str) - 1;
    k = 0;
    while (i - k >= 0 && j - k >= 0)
    {
        if (j - k == 0)
            return (true);
        if (str[j - k] != file[i - k])
            return (false);
        k++;
    }
    return (false);
}

int ft_strcmp_wildcard(char *file, char *str)
{
    int i;

    i = 0;
    while (file[i] || str[i])
    {
        if (str[i] == '*')
            return (i+1);
        if (str[i] != file[i])
            return (0);
        i++;
    }
    return (i+1);
}

int ft_strcmp_recursive(char *namefile, char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (namefile[j] && !i)
    {
        i = ft_strcmp_wildcard(namefile + j, str);
        j++;
    }
    if (!i)
        return (0);
    if (ft_find_chr(str + i, '*'))
    {
        if (i == 1)
            i = ft_strcmp_recursive(namefile, str + i);
        else
            i = ft_strcmp_recursive(namefile + j + i - 1, str + i);
    }    
    else
        i = ft_strcmp_end_start_wildcard(namefile, str + i);
    return (i);
}

void ft_lstcomp_wildcard(t_files **files, char *str)
{
    t_files *tmp;
    t_files *tmp2;
    int e;

    tmp = *files;
    while (tmp)
    {
        printf("name = %s\n", tmp->name);
        e = ft_strcmp_recursive(tmp->name, str);
        printf ("e = %d\n\n", e);
        if (!e)
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
