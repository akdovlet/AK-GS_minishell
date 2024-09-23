/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:10:20 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/23 17:17:18 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int creat_node_n_add_back_if_str(t_files **files, char *tmp)
{
    t_files *new;

    if (!tmp)
        return (perror("minishell: ft_strndup failed"), 1);
    if (tmp[0] == '\0')
        return (0);
    new = ft_lstnew_files(tmp);
    if (!new)
        return (1);
    ft_lst_add_back_files(files, new);
    return (0);
}

static int copy_squote(char *str, int *i, t_files **files)
{
    int j;
    char *tmp;

    j = *i + 1;
    while (str[j] && str[j] != '\'')
        j++;
    tmp = ft_strndup(str + *i + 1, j - *i - 1);
    if (ft_new_lst_add_back_files(files, ft_lstnew_files(tmp)))
        return (1);
    *i = j + 1;
    return (0);
}

// probleme avec cette liste chaine on strdup 2x la meme chaine
static int copy_dquotes(char *str, int *i, t_files **files, t_data *data)
{
    int j;
    char *tmp;

    j = *i + 1;
    while (str[j] && str[j] != '\"')
    {
        if (str[j] == '$' && ft_isalpha(str[j + 1]))
        {
            if (creat_node_n_add_back_if_str(files, ft_strndup(str + j, *i - j)))
                return (1);
            if (copy_var(str, &j, files, data) == 1)
                return (1);
            *i = j - 1;
        }
        else
            j++;
    }
    tmp = ft_strndup(str + *i + 1, j - *i - 1);
    if (creat_node_n_add_back_if_str(files, tmp))
        return (1);
    *i = j + 1;
    return (0);
}

int tri_char(char *str, int *i, t_files **files, t_data *data)
{
    if (str[*i] == '\'')
    {
        if (copy_squote(str, i, files))
            return (1);
    }
    else if (str[*i] == '\"')
    {
        if (copy_dquotes(str, i, files, data))
            return (1);
    }
    else if (str[*i] == '$' && ft_isalpha(str[*i + 1]))
    {
        if (copy_var(str, i, files, data) == 1)
            return (1);
    }
    return (0);
}

// probleme tout ce qui ne rentre pas dans l'une des fonctions ne va pas etre copier
// dans notre liste chainee = potentiellement reglé
int expand_str(char *str, t_data *data, t_files **files)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"' || (str[i] == '$' && ft_isalpha(str[i + 1])))
        {
            if (creat_node_n_add_back_if_str(files, ft_strndup(str + j, i - j)))
                    return (1);
            if (tri_char(str, &i, files, data))
                return (1);
            j = i;
        }
        else
            (i)++;
    }
    if (creat_node_n_add_back_if_str(files, ft_strndup(str + j, i - j)))
        return (1);
    return (0);
}

int expand_tab_of_cmd(char **tab_cmd, t_data *data)
{
    int i;
    t_files *files;

    i = 0;
    files = NULL;
    while (tab_cmd[i])
    {
        if (expand_str(tab_cmd[i], data, &files))
            return (1);
        free(tab_cmd[i]);
        tab_cmd[i] = write_files_expand(files);
        ft_free_lst_files_expand(&files);
        if (!tab_cmd[i])
            return (1);
        i++;
    }
    return (true);
}
