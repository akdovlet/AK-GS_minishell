/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:11:27 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/19 10:07:04 by gschwand         ###   ########.fr       */
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
	t_files	*node;
	t_files	*tmp;

	node = *files;
	while (node && node->name[0] == '.')
	{
		tmp = node;
		node = node->next;
	}
	tmp->next = NULL;
	ft_free_lst_files_expand(&node);
}

int find_n_s(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	return (i);
}

// find pattern return 0 if the pattern is not in the file
// return the index of the last caracter of the pattern
int	find_pattern(char *file, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (file[i])
	{
		if (file[i] == str[j])
		{
			while (file[i] == str[j] && str[j] && file[i])
			{
				i++;
				j++;
				if ((!str[j] && !file[i]) || str[j] == '*')
					return (i);
			}
			j = 0;
			i--;
		}
		i++;
	}
	return (0);
}

int lst_comp_file_str(char *file, char *str)
{
	int i;

	i = 0;
	if (!str[0] || (str[0] == '*' && str[1] == '\0'))
		return (0);
	else if (str[0] != '*' && !ft_strncmp(file, str, find_n_s(str)))
		return (lst_comp_file_str(file + find_n_s(str), str + find_n_s(str)));
	else if (str[0] == '*' && str[1] == '*')
		return (lst_comp_file_str(file, str + 1));
	else if (str[0] == '*' && str[1] != '*')
	{
		i = find_pattern(file, str + 1);
		if (i)
			return (lst_comp_file_str(file + i, str + 1 + find_n_s(str + 1)));	
	}
	return (1);
}

void sort_files(t_files **files, char *str)
{
	t_files	*tmp;
	t_files	*node;

	tmp = *files;
	while (tmp && lst_comp_file_str(tmp->name, str))
	{
		*files = (*files)->next;
		free(tmp->name);
		free(tmp);
		tmp = *files;
	}
	while (tmp && tmp->next)
	{
		if (lst_comp_file_str(tmp->next->name, str))
		{
			node = tmp->next;
			tmp->next = tmp->next->next;
			free(node->name);
			free(node);
		}
		else
			tmp = tmp->next;
	}
}

char *expand_wildcard(char *str)
{
	char *res;
	t_files *files;

	files = NULL;
	files = ft_recover_files();
	ft_sort_alpha_files(&files);
	if (str[0] != '.')
		del_files_hidden(&files);
	else
		del_files_not_hidden(&files);
	sort_files(&files, str);
	if (files == NULL)
		return (str);
	res = write_files(files);
	ft_free_lst_files_expand(&files);
	free(str);
	return (res);
}
