/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_first_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:28:43 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/12 19:23:12 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expand.h"

char	**ft_wildcard_first_cmd(char **cmd)
{
	t_files	*files;

	files = NULL;
	if (ft_find_chr_exec(cmd[0], '*') == 1)
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
