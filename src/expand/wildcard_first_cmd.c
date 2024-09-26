/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_first_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:28:43 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/26 16:16:23 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "exec.h"

char **ft_wildcard_first_cmd(char **cmd)
{
    t_files	*files;

	files = NULL;
	if (ft_find_chr_exec(cmd[0], '*'))
    {
        files = expand_wildcard(&files, cmd[0]);
		if (!files)
			return (NULL);
		files = tab_to_lst_files(&files, cmd + 1);
		if (!files)
			return (NULL);
		free_tab(cmd);
		cmd = ft_lst_to_tab(&files);
		if (!cmd)
			return (NULL);
		ft_free_lst_files_expand(&files);
    }
	return (cmd);
}
