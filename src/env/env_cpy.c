/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:12:54 by akdovlet          #+#    #+#             */
/*   Updated: 2024/06/27 13:56:14 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

bool	copy_env(t_env **cpy, char **env)
{
	int		i;
	t_env	*new;

	i = 0;
	while (env[i])
	{
		new = ft_envnew(env[i]);
		if (!new)
			return (false);
		ft_add_back(cpy, new);
		i++;
	}
	return (true);
}
