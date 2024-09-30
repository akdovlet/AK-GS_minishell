/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:32:23 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/30 17:27:57 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	ft_strcasecmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (tolower(*s1) != tolower(*s2))
			return (tolower(*s1) - tolower(*s2));
		s1++;
		s2++;
	}
	return (tolower(*s1) - tolower(*s2));
}

int ft_find_chr_exec(char *str, char c)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (-1);
}
