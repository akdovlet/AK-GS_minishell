/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:04:41 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/12 19:37:17 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_only_digit(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[0] == '-')
		n = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (2);
		i++;
	}
	if (check_overflow(str + 1, n))
		return (2);
	return (0);
}

// Fonction pour gérer les erreurs d'argument non numérique
static int	handle_numeric_argument_error(char *arg, t_data *data)
{
	if (!data->fork)
		ft_dprintf(2, "exit\n");
	ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", arg);
	return (clear_exit(data, 2), 2);
}

// Fonction pour gérer le cas de trop d'arguments
static int	handle_too_many_arguments(t_data *data)
{
	if (!data->fork)
		ft_dprintf(2, "exit\n");
	ft_dprintf(2, "minishell: exit: too many arguments\n");
	data->status = 127;
	return (127);
}

// Fonction pour gérer la sortie avec un seul argument numérique
static int	handle_exit_with_argument(char *arg, t_data *data)
{
	int	exit_code;

	if (check_only_digit(arg))
		return (handle_numeric_argument_error(arg, data));
	exit_code = (unsigned char)ft_atoi(arg);
	if (!data->fork)
		ft_dprintf(2, "exit\n");
	clear_exit(data, exit_code);
	return (exit_code);
}

// Fonction principale
int	ft_exit(char **tab, t_data *data)
{
	if (tab[1] && tab[2])
	{
		if (check_only_digit(tab[1]))
			return (handle_numeric_argument_error(tab[1], data));
		return (handle_too_many_arguments(data));
	}
	if (tab[1])
		return (handle_exit_with_argument(tab[1], data));
	if (!data->fork)
		ft_dprintf(2, "exit\n");
	clear_exit(data, data->status);
	return (0);
}
