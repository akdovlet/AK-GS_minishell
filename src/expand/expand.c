/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:10:20 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/18 08:59:40 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

// La priorite se trouve sur les wildcards avec les expensions de variables

int has_dollar_sign_outside_quotes(char *str)
{
    int i;
    int quote;
    int dquote;
    
    i = 0;
    quote = 0;
    dquote = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            quote += 1;
        else if (str[i] == '$' && quote % 2 == 0)
            return (1);
        i++;
    }
    if (quote && dquote)
        return (2);
    return (0);
}

char *ft_supp_quotes(char *str)
{
    char *res;
    int lenres;

    lenres = ft_strlen_wo_c(str, '\'');
    res = malloc(sizeof(char) * (lenres + 1));
    if (!res)
        return (NULL);
    ft_strlcpy_wo_c(res, str, '\'');
    free(str);
    return (res);
}

char *ft_supp_dquotes(char *str)
{
    char *res;
    int lenres;

    lenres = ft_strlen_wo_c(str, '\"');
    res = malloc(sizeof(char) * (lenres + 1));
    if (!res)
        return (NULL);
    ft_strlcpy_wo_c(res, str, '\"');
    free(str);
    return (res);
}

// static int find_quotes(char *str)
// {
//     int i;

//     i = 0;
//     if (!str)
//         return (0);
//     while (str[i])
//     {
//         if (str[i] == '\'')
//             return (1);
//         else if (str[i] == '\"')
//             return (2);
//         i++;
//     }
//     return (0);
// }

static int copy_squote(char *str, int *i, t_files **files)
{
    int j;
    char *tmp;

    printf("copy_squote\n");
    j = *i + 1;
    while (str[j] && str[j] != '\'')
        j++;
    tmp = ft_strndup(str + *i + 1, j - *i - 1);
    if (ft_new_lst_add_back_files(files, ft_lstnew_files(tmp)))
        return (1);
    *i = j + 1;
    return (0);
}

int creat_node_n_add_back_if_str(t_files **files, char *tmp)
{
    t_files *new;

    if (tmp[0] == '\0')
        return (0);
    if (!tmp)
        return (1);
    new = ft_lstnew_files(tmp);
    if (!new)
        return (1);
    ft_lst_add_back_files(files, new);
    return (0);
}

// quit lorsque la variable n'existe pas
// sorti aussi des dquotes
// static int copy_var(char *str, int *i, t_files **files, t_data *data)
// {
//     int j;
//     char *tmp;
//     t_files *new;
//     t_env *node;
    
//     j = *i + 1;
//     while (str[j] && str[j] != '\'' && str[j] != '\"' && str[j] != '$' && str[j] != ' ')
//         j++;
//     tmp = ft_strndup(str + *i + 1, j - *i - 1);
//     if (strcmp(tmp, "?") == 0)
//     {
//         tmp = ft_itoa(data->status);
//         if (!tmp)
//             return (1);
//     }
//     else
//     {
//         node = ft_check_key(&data->env, tmp);
//         if (!node)
//         {
//             *i = j;
//             return (free(tmp), 2);
//         }
//         tmp = node->value;
//     }
//     new = ft_lstnew_files(tmp);
//     if (!new)
//         return (1);
//     ft_lst_add_back_files(files, new);
//     *i = j;
//     return (0);
// }

static char *extract_var_name(char *str, int *i) 
{
    int j;
    int tmp;
    
    j = *i + 1;
    while (str[j] && ft_isalnum(str[j]))
        j++;
    tmp = *i;
    *i = j;
    return (ft_strndup(str + tmp + 1, j - tmp - 1));
}

static char *get_var_value(char *var_name, t_data *data)
{
    char *value;
    t_env *node;
    
    if (strcmp(var_name, "?") == 0) 
    {
        value = ft_itoa(data->status);
        if (!value)
            return (NULL);
        return (value);
    }
    node = ft_check_key(&data->env, var_name);
    if (!node)
        return NULL;
    return (node->value);
}

static int create_and_add_file(char *value, t_files **files) 
{
    t_files *new;
    
    new = ft_lstnew_files(value);
    if (!new)
        return (1);
    ft_lst_add_back_files(files, new);
    return (0);
}

static int copy_var(char *str, int *i, t_files **files, t_data *data)
{
    char *var_name;
    char *value;
    int result;

    var_name = extract_var_name(str, i);
    if (!var_name)
        return (1);

    value = get_var_value(var_name, data);
    if (!value)
        return (free(var_name), 2);
    result = create_and_add_file(value, files);
    return (free(var_name), result);
}

// probleme avec cette liste chaine on strdup 2x la meme chaine
static int copy_dquotes(char *str, int *i, t_files **files, t_data *data)
{
    int j;

    j = *i + 1;
    while (str[j] && str[j] != '\"' && j < 100)
    {
        if (str[j] == '$')
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
    if (creat_node_n_add_back_if_str(files, ft_strndup(str + j, *i - j)))
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
    else if (str[*i] == '$')
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
    int *i;
    int j;
    
    i = malloc(sizeof(int *));
    *i = 0;
    j = 0;
    while (str[*i])
    {
        if (str[*i] == '\'' || str[*i] == '\"' || str[*i] == '$')
        {
            if (creat_node_n_add_back_if_str(files, ft_strndup(str + j, *i - j)))
                    return (1);
            if (tri_char(str, i, files, data))
                return (1);
            j = *i;
        }
        else
            (*i)++;
    }
    if (creat_node_n_add_back_if_str(files, ft_strndup(str + j, *i - j)))
        return (1);
    return (0);
}

int expand_tab_of_cmd(char **tab_cmd, t_data *data)
{
    int i;
    t_files *files;

    i = 0;
    files = NULL;
    while (tab_cmd[i] && i < 10)
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

// int expand_tab_of_cmd(char **tab_cmd, t_env *env)
// {
//     int i;
//     (void)env;

//     i = 0;
//     while (tab_cmd[i])
//     {
//         if (find_quotes(tab_cmd[i]) == 1)
//             tab_cmd[i] = ft_supp_quotes(tab_cmd[i]);
//         else if (find_quotes(tab_cmd[i]) == 2)
//         {
//             tab_cmd[i] = ft_supp_dquotes(tab_cmd[i]);
//             if (ft_find_chr(tab_cmd[i], '$'))
//                 tab_cmd[i] = expand_var(tab_cmd[i], env);
//         }
//         else if (ft_find_chr(tab_cmd[i], '$'))
//             tab_cmd[i] = expand_var(tab_cmd[i], env);
//         i++;
//     }
//     return (true);
// }

// int ft_expand(t_cmdlist *lst, t_env *env)
// {
//     while(lst)
//     {
//         expand_tab_of_cmd(lst->cmd, env);
//         if (lst->cmd[1])
//         {
//             if (ft_wildcard(lst->cmd))
//                 return (false);
//         }
//         lst = lst->next;
//     }
// }
