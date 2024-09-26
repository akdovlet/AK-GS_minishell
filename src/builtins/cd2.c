/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:27:13 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/26 14:27:27 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	go_home(t_env **env)
{
	t_env	*tmp;

	tmp = ft_check_key(env, "HOME");
	if (tmp == NULL)
	{
		ft_dprintf(2, "minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(tmp->value))
		return (perror("minishell: cd failed"), 1);
	return (0);
}
