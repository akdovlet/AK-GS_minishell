/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:11:27 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/15 16:41:48 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "exec.h"



void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_files	*sort_files(t_files *files, char *str)
{
	t_files	*tmp;

	ft_lstcomp_wildcard(&files, str);
	if (!files)
	{
		tmp = files_new(str);
		if (!files)
			return (NULL);
		files = tmp;
	}
	return (files);
}

// del all files that start with a '.' in the list
void	del_files_hidden(t_files **files)
{
	t_files	*tmp;
	t_files	*node;

	node = *files;
	while (*files && (*files)->name[0] == '.')
	{
		*files = (*files)->next;
		free(node->name);
		free(node);
		node = *files;
	}
	tmp = *files;
	while (tmp)
	{
		if (tmp->next && tmp->next->name[0] == '.')
		{
			node = tmp->next;
			tmp->next = tmp->next->next;
			free(node->name);
			free(node);
		}
		tmp = tmp->next;
	}
}

void del_files_not_hidden(t_files **files)
{
	t_files	*tmp;
	t_files	*node;

	node = *files;
	while (*files && (*files)->name[0] != '.')
	{
		*files = (*files)->next;
		free(node->name);
		free(node);
		node = *files;
	}
	tmp = *files;
	while (tmp)
	{
		if (tmp->next && tmp->next->name[0] != '.')
		{
			node = tmp->next;
			tmp->next = tmp->next->next;
			free(node->name);
			free(node);
		}
		tmp = tmp->next;
	}
}

char *expand_wildcard_2(char *str)
{
	char *res;
	t_files *files;

	res = NULL;
	(void)str;
	files = ft_recover_files();
	ft_sort_alpha_files(&files);
	if (str[0] != '.')
		del_files_hidden(&files);
	else
		del_files_not_hidden(&files);
	ft_print_lst_files(files);
	return (res);
}






///////////////////////////////////////////////

t_files	*expand_wildcard(t_files **files, char *str)
{
	t_files	*files_tmp;

	files_tmp = ft_recover_files();
	ft_sort_alpha_files(&files_tmp);
	del_files_hidden(&files_tmp);
	if (!files_tmp)
		return (ft_free_lst_files(files), NULL);
	files_tmp = sort_files(files_tmp, str);
	if (!files_tmp)
	{
		files_tmp = files_new_dup(str);
		if (!files_tmp)
			return (ft_free_lst_files(files), NULL);
	}
	files_addback(files, files_tmp);
	return (*files);
}

char	**ft_wildcard(char **tab_cmd)
{
	t_files	*files;
	t_files	*tmp;
	int		i;

	files = NULL;
	i = 0;
	while (tab_cmd[i])
	{
		if (ft_find_chr_exec(tab_cmd[i], '*') == 1)
			files = expand_wildcard(&files, tab_cmd[i]);
		else
		{
			tmp = files_new_dup(tab_cmd[i]);
			if (!tmp)
				return (NULL);
			files_addback(&files, tmp);
		}
		i++;
	}
	free_tab(tab_cmd);
	tab_cmd = ft_lst_to_tab(&files);
	if (!tab_cmd)
		return (NULL);
	return (tab_cmd);
}
