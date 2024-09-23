/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:37:13 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/23 19:20:35 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char *extract_var_name(char *str, int *i) 
{
    int j;
    int tmp;
    
    j = *i + 1;
    if (str[j] == '?')
    {
        *i = j + 1;
        return (ft_strdup("?"));
    }
    while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
        j++;
    tmp = *i;
    *i = j;
    printf("----------------\nstr[%d] = %c\n---------------\n", *i, str[j]);
    return (ft_strndup(str + tmp + 1, j - tmp - 1));
}

static char *get_var_value(char *var_name, t_data *data)
{
    char *value;
    t_env *node;
    
    if (!ft_strcmp(var_name, "?")) 
    {
        value = ft_itoa(data->status);
        if (!value)
            return (NULL);
        return (value);
    }
    node = ft_check_key(&data->env, var_name);
    if (!node)
        return (NULL);
    return (node->value);
}

static int create_and_add_file(char *value, t_files **files) 
{
    t_files *new;
    
    new = ft_lstnew_files_dup(value);
    if (!new)
        return (1);
    ft_lst_add_back_files(files, new);
    return (0);
}

int copy_var(char *str, int *i, t_files **files, t_data *data)
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
