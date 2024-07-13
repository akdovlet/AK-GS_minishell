/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_dprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:18:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/13 11:31:01 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	arg;
	int		wrote;

	va_start(arg, str);
	wrote = ak_printf(fd, str, &arg);
	va_end(arg);
	return (wrote);
}
