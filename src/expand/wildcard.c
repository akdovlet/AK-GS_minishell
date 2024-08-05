/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:11:27 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/05 17:05:16 by gschwand         ###   ########.fr       */
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
    new->name = str;
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
        tmp = malloc(sizeof(t_files));
        if (!tmp)
        {
            perror("malloc");
            return (NULL);
        }
        tmp = ft_lstnew_files(entry->d_name);
        ft_lst_add_back_files(&files, tmp);
    }
    closedir(dir);
    return (files);
}

// res will return all the files who correspond to the wildcard
char  *expand_wildcard(char *str)
{
    t_files *files;
    char *res;
    
    (void)str;
    res = NULL;
    files = ft_recover_files();
    // res = sort_files(files, str);
    ft_print_lst_files(files);
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
