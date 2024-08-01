/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:10:20 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/01 08:32:01 by gschwand         ###   ########.fr       */
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

void print_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        printf("%s\n", tab[i]);
        i++;
    }
}

int expand_tab_of_cmd(char **tab_cmd, t_env *env)
{
    int i;

    i = 0;
    while (tab_cmd[i])
    {
        if (has_dollar_sign_outside_quotes(tab_cmd[i])) /* faux l'expand peut se faire aussi dans un mot, et faut supp les ' et " */
        {
            tab_cmd[i] = expand_var(tab_cmd[i], env);
            if (!tab_cmd[i])
                return(false);
        }
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
