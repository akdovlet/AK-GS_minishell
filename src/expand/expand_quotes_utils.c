/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:57:37 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/14 14:14:15 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int ft_find_chr(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int ft_strlen_wo_c(const char *str, char c)
{
    int len = 0;
    while (*str) 
    {
        if (*str != c) 
            len++;
        str++;
    }
    return len;
}

void ft_strlcpy_wo_c(char *dst, const char *src, char c)
{
    while (*src) {
        if (*src != c) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}
