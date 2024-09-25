/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_first_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:47:44 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/25 15:57:59 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expand.h"

t_files *tab_to_lst_files(t_files **files, char **tab)
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

static char **strdup_tab(char **cmd)
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


t_files *handle_file_list_expansion(char **cmd)
{
    t_files *files_second;
    
    files_second = NULL;
    files_second = tab_to_lst_files(&files_second, cmd);
    if (!files_second)
        return (NULL);
    return (files_second);
}

int handle_expansion(char **cmd, t_data *data, t_files **files_first)
{
    t_files *tmpNode;
    char *tmp;


    if (expand_str(cmd[0], data, files_first))
        return (1);
    tmp = (*files_first)->next->name;
    (*files_first)->next->name = ft_strjoin((*files_first)->name, (*files_first)->next->name);
    if (!(*files_first)->name)
        return (1);
    tmpNode = *files_first;
    *files_first = (*files_first)->next;
    free(tmpNode->name);
    free(tmpNode);
    free(tmp);
    return (0);
}

int handle_variable(char **cmd, t_data *data, t_files **files_first)
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


char **expand_first_cmd(char **cmd, t_data *data)
{
    t_files *files_first = NULL;
    t_files *files_second = NULL;

    if (ft_find_chr_exec(cmd[0], '$') == -1)
        return (strdup_tab(cmd));
    if (handle_variable(cmd, data, &files_first))
        return (NULL);
    if (handle_expansion(cmd, data, &files_first))
        return (NULL);
    if (cmd[1])
    {
        files_second = handle_file_list_expansion(cmd + 1);
        if (!files_second)
            return (NULL);
        ft_lst_add_back_files(&files_first, files_second);
    }
    cmd = ft_lst_to_tab(&files_first);
    ft_free_lst_files_expand(&files_first);
    return (cmd);
}
