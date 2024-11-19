/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:51:44 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/19 14:29:03 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_change_value(t_env *node, char *str)
{
	char	*tmp;

	free(node->value);
	if (ft_strchr(str, '='))
	{
		tmp = ft_strdup(str + ft_strlen(node->key) + 1);
		if (!tmp)
			return (1);
		str = remove_quotes(tmp);
		free(tmp);
		if (!str)
			return (1);
		node->value = str;
	}
	else
		node->value = NULL;
	return (0);
}

int	check_alnum_str(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] != '=')
		return (2);
	return (1);
}
