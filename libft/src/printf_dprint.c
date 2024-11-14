/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_dprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:18:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/14 16:19:46 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include <stdio.h>

int	ak_printf(int fd, const char *str, va_list *arg)
{
	int		i;
	t_print	data;

	i = -1;
	data = (t_print){};
	data.fd = fd;
	data.buffer[MAX_BUFFER] = '\0';
	while (str[++i])
	{
		if (str[i] == '%')
			data.wrote += ft_ddraft(str[++i], &data, arg);
		else
		{
			data.buffer[data.j] = str[i];
			data.j++;
		}
		if (data.j >= MAX_BUFFER)
			print_buffer(data.fd, data.buffer, &data.j, &data.err);
	}
	print_buffer(fd, data.buffer, &data.j, &data.err);
	if (data.err)
		return (-1);
	return (data.wrote);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	arg;
	int		wrote;

	va_start(arg, str);
	wrote = ak_printf(fd, str, &arg);
	va_end(arg);
	return (wrote);
}
