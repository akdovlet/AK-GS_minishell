/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_dprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:18:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/21 13:10:10 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ak_printf(int fd, const char *str, va_list *arg)
{
	int		i;
	t_print	data;

	i = -1;
	data.j = 0;
	data.wrote = 0;
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
			print_buffer(data.fd, data.buffer, &data.j);
	}
	print_buffer(fd, data.buffer, &data.j);
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
