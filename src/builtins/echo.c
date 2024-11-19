/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:00:28 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/19 13:20:06 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	parse_flag(char *str, int *flag)
{
	int	i;

	i = 0;
	if (!(str[0] == '-' && str[1] == 'n'))
		return (0);
	else
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	*flag = 1;
	return (1);
}

int	parse_nl(char **strs, int *i)
{
	int	flag;

	flag = 0;
	while (strs[*i])
	{
		if (!parse_flag(strs[*i], &flag))
			return (flag);
		(*i)++;
	}
	return (flag);
}

int	builtin_echo(char **strs)
{
	int	i;
	int	err;
	int	nl;

	i = 1;
	err = 0;
	nl = parse_nl(strs, &i);
	while (strs[i])
	{
		err = ft_dprintf(STDOUT_FILENO, "%s", strs[i]);
		if (strs[i + 1])
			err = ft_dprintf(STDOUT_FILENO, " ");
		i++;
	}
	if (!nl)
		err = ft_dprintf(STDOUT_FILENO, "\n");
	if (err == -1)
		return (perror("minishell: echo: write error"), 1);
	return (0);
}
