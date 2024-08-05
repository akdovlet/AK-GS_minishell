/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_debugg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:02:04 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/05 16:55:31 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void ft_print_lst_files(t_files *files)
{
    t_files *tmp;

    tmp = files;
    while (tmp)
    {
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
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
