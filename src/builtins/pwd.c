/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:03:00 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/08 07:03:13 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_pwd(void)
{
    char *buf;
    buf = getcwd(NULL, 0);
    if (buf == NULL)
    {
        ft_putstr_fd("Error: getcwd failed\n", 2);
        return (1);
    }
    ft_putstr_fd(buf, 1);
    ft_putstr_fd("\n", 1);
    free(buf);
    return (0);
}
