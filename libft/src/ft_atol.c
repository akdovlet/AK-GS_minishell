/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:47:46 by akdovlet          #+#    #+#             */
/*   Updated: 2024/04/09 17:42:17 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	flip;
	long	nb;

	i = 0;
	nb = 0;
	flip = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			flip *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	return (nb * flip);
}
