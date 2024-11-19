/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:11:27 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/19 13:29:13 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expand.h"

int	find_n_s(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	return (i);
}

// find pattern return 0 if the pattern is not in the file
// return the index of the last caracter of the pattern
int	find_pattern(char *file, char *str)
{
	int	i;
	int	j;

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

int	lst_comp_file_str(char *file, char *str)
{
	int	i;

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

void	sort_files(t_files **files, char *str)
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

char	*expand_wildcard(char *str)
{
	char	*res;
	t_files	*files;

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
