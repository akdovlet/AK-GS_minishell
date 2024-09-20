/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:12:54 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/20 17:32:51 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

bool	env_copy(t_env **cpy, char **env)
{
	int		i;
	t_env	*new;

	i = 0;
	while (env[i])
	{
		new = env_new(env[i]);
		if (!new)
			return (1);
		env_add_back(cpy, new);
		i++;
	}
	return (0);
}
