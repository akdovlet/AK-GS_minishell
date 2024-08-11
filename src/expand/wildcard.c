/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:11:27 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/11 15:57:20 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

// exec de "ls" et recup de la liste dans un dossier tmp
// fonctionne comme l'expenion de variable 
// Sortie d'une string avec tous les files demande dans e dossier courant

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

char *write_files(t_files *files)
{
    t_files *tmp;
    char *res;
    int lenres;

    tmp = files;
    lenres = 0;
    while (tmp)
    {
        lenres += ft_strlen(tmp->name) + 1;
        printf("lenres = %d\n", lenres);
        printf("tmp->name = %s\n", tmp->name);
        tmp = tmp->next;
    }
    res = ft_calloc(sizeof(char), lenres + 1);
    if (!res)
        return (perror("malloc"), NULL);
    tmp = files;
    while (tmp)
    {
        printf("tmp->name = %s\n", tmp->name);
        ft_strlcat(res, tmp->name, lenres + 1);
        ft_strlcat(res, " ", lenres + 1);
        tmp = tmp->next;
    }
    return (res);
}

void ft_free_lst_files(t_files *files)
{
    t_files *tmp;

    while (files)
    {
        tmp = files;
        files = files->next;
        free(tmp);
    }
}

// add dquotes to file name
char *sort_files(t_files *files, char *str)
{
    char *res;

    ft_print_lst_files(files);
    printf("\n");
    ft_lstcomp_wildcard(&files, str, ft_strcmp_start_end_wildcard);
    ft_lstcomp_wildcard(&files, str, ft_strcmp_end_start_wildcard);
    ft_print_lst_files(files);
    res = write_files(files);
    ft_free_lst_files(files);
    return (res);
}

// remove the first two files
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
