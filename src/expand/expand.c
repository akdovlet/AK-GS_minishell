/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:10:20 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/01 14:49:18 by gschwand         ###   ########.fr       */
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

int expand_tab_of_cmd(char **tab_cmd, t_env *env)
{
    int i;
    (void)env;

    i = 0;
    while (tab_cmd[i])
    {
        if (ft_strchr(tab_cmd[i], '\''))
            tab_cmd[i] = ft_supp_quotes(tab_cmd[i]);
        else if (ft_strchr(tab_cmd[i], '\"'))
        {
            tab_cmd[i] = ft_supp_dquotes(tab_cmd[i]);
            // tab_cmd[i] = expand_var(tab_cmd[i], env);
        }
        else if (ft_find_chr(tab_cmd[i], '$') != -1)
            tab_cmd[i] = expand_var(tab_cmd[i], env);
        i++;
    }
    print_tab(tab_cmd);
    return (true);
}

// int ft_expand(t_cmdlist *lst, t_env *env)
// {
//     while(lst)
//     {
//         expand_tab_of_cmd(lst->cmd, env);
//         lst = lst->next;
//     }
// }
