/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_first_cmd2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:44:04 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/25 17:44:38 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expand.h"

t_files	*tab_to_lst_files(t_files **files, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (creat_node_n_add_back(files, tab[i]))
			return (ft_free_lst_files(files), NULL);
		i++;
	}
	return (*files);
}

char	**strdup_tab(char **cmd)
{
	int		i;
	char	**new_cmd;

	i = 0;
	while (cmd[i])
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 1));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		new_cmd[i] = ft_strdup(cmd[i]);
		if (!new_cmd[i])
			return (free_tab(new_cmd), NULL);
		i++;
	}
	new_cmd[i] = NULL;
	return (new_cmd);
}
