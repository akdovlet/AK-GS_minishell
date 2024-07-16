/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 07:21:54 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/08 07:59:22 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char *ft_strjoin_export(char *s1, char *s2)
{
    char *str;
    int lens1;
    int lens2;

    lens1 = ft_strlen(s1);
    lens2 = ft_strlen(s2);
    str = malloc((lens1 + lens2 + 2) * sizeof(char));
    if (str == NULL)
        return (NULL);
    ft_strlcpy(str, s1, lens1 + 1);
    str[lens1] = '=';
    ft_strlcat(str, s2, lens1 + lens2 + 2);
    return (str);
}

int ft_export(char *name, char *value)
{
    if (name == NULL || value == NULL)
        return (ft_putstr_fd("\n", 2));
    
}