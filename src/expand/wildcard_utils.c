/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:32:23 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/26 15:36:10 by akdovlet         ###   ########.fr       */
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
