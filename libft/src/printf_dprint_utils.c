/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_dprint_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:30:21 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/13 11:33:09 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	print_buffer(int fd, char *buffer, int *j)
{
	int	wrote;

	wrote = *j;
	if (*j == 0)
		return (0);
	write(fd, buffer, *j);
	*j = 0;
	return (wrote);
}

int	string_tobuffer(char *str, t_print *data)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (data->j >= MAX_BUFFER)
			data->wrote += print_buffer(data->fd, data->buffer, &data->j);
		data->buffer[data->j] = str[i];
		data->j++;
		i++;
	}
	return (i);
}

int	char_tobuffer(int c, t_print *data)
{
	if (data->j >= MAX_BUFFER)
		data->wrote += print_buffer(data->fd, data->buffer, &data->j);
	data->buffer[data->j] = c;
	data->j++;
	return (1);
}

int	ft_ddraft(char flag, t_print *data, va_list *arg)
{
	int	wrote;

	wrote = 0;
	if (flag == 's')
		wrote += string_tobuffer(va_arg(*arg, char *), data);
	if (flag == 'c')
		wrote += char_tobuffer(va_arg(*arg, int), data);
	else
		return (-1);
	return (wrote);
}

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