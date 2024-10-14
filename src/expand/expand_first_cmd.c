/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_first_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:47:44 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/14 12:26:44 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expand.h"

t_files	*handle_file_list_expansion(char **cmd)
{
	t_files	*files_second;

	files_second = NULL;
	files_second = tab_to_lst_files(&files_second, cmd);
	if (!files_second)
		return (NULL);
	return (files_second);
}

int	handle_expansion(char **cmd, t_data *data, t_files **files_first)
{
	t_files	*tmp_node;
	char	*tmp;

	if (expand_str(cmd[0], data, files_first))
		return (1);
	tmp = (*files_first)->next->name;
	(*files_first)->next->name = ft_strjoin((*files_first)->name,
			(*files_first)->next->name);
	if (!(*files_first)->name)
		return (1);
	tmp_node = *files_first;
	*files_first = (*files_first)->next;
	free(tmp_node->name);
	free(tmp_node);
	free(tmp);
	return (0);
}

int	handle_variable(char **cmd, t_data *data, t_files **files_first)
{
	if (cmd[0][0] == '$')
	{
		if (check_var(cmd[0], data))
		{
			*files_first = tab_to_lst_files(files_first, cmd + 1);
			if (!files_first)
				return (1);
			return (0);
		}
		if (expand_str(cmd[0], data, files_first))
			return (1);
	}
	return (0);
}

char	**expand_first_cmd(char **cmd, t_data *data)
{
	t_files	*files_first;
	t_files	*files_second;

	files_first = NULL;
	files_second = NULL;
	if (ft_find_chr_exec(cmd[0], '$') == -1)
		return (cmd);
	if (handle_variable(cmd, data, &files_first))
		return (free_tab(cmd), NULL);
	if (!files_first)
	{
		if (handle_expansion(cmd, data, &files_first)) //leak potentiel ici
			return (free_tab(cmd), NULL);
	}
	if (cmd[1])
	{
		files_second = handle_file_list_expansion(cmd + 1);
		if (!files_second)
			return (NULL);
		files_add_back(&files_first, files_second);
	}
	free_tab(cmd);
	cmd = ft_lst_to_tab(&files_first);
	ft_free_lst_files_expand(&files_first);
	// if (ft_find_chr_exec(cmd[0], '$') != -1)
	// 	return (expand_first_cmd(cmd, data));
	return (cmd);
}
