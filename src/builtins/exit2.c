/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:17:16 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/27 16:30:12 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int check_overflow(char *str, int n)
{
    int len;

    len = ft_strlen(str);
    if (len > 19)
        return (2);
    
    if (n == 1)
    {
        if (len == 19 && ft_strncmp(str, "9223372036854775808", 19) > 0)
            return (2);
    }
    else
    {
        if (len == 19 && ft_strncmp(str, "9223372036854775807", 19) > 0)
            return (2);
    }
    return (0);
}