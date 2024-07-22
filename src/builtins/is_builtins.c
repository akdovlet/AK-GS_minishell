/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:50:55 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/16 16:07:17 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtins(char *str)
{
    if (!ft_strcmp(str, "echo"))
        return (1);
    if (!ft_strcmp(str, "cd"))
        return (1);
    if (!ft_strcmp(str, "pwd"))
        return (1);
    if (!ft_strcmp(str, "export"))
        return (1);
    if (!ft_strcmp(str, "unset"))
        return (1);
    if (!ft_strcmp(str, "env"))
        return (1);
    if (!ft_strcmp(str, "exit"))
        return (1);
    return (0);
}
