/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:06:16 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/14 16:17:36 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include "libft.h"
# define MAX_BUFFER 4096

typedef struct s_print
{
	char	buffer[MAX_BUFFER + 1];
	int		wrote;
	int		j;
	int		fd;
	int		err;
}	t_print;

int	ft_dprintf(int fd, const char *str, ...);
int	print_buffer(int fd, char *buffer, int *j, int *err);
int	string_tobuffer(char *str, t_print *data);
int	char_tobuffer(int c, t_print *data);
int	ft_ddraft(char flag, t_print *data, va_list *arg);
int	ak_printf(int fd, const char *str, va_list *arg);

#endif
