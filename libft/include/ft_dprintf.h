/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:06:16 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/18 21:29:42 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include "libft.h"

int	ft_dprintf(int fd, const char *str, ...);

# define MAX_BUFFER 4096

typedef struct s_print
{
	char	buffer[MAX_BUFFER + 1];
	int		wrote;
	int		j;
	int		fd;
}	t_print;

#endif
