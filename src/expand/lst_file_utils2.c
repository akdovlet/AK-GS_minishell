/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:37:59 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/25 15:42:20 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	ft_free_lst_files(t_files **files)
{
	t_files	*tmp;

	while (files)
	{
		tmp = *files;
		*files = (*files)->next;
		free(tmp);
	}
}

void	ft_free_lst_files_expand(t_files **files)
{
	t_files	*tmp;

	while (*files)
	{
		tmp = (*files)->next;
		free((*files)->name);
		free(*files);
		*files = tmp;
	}
}

t_files	*ft_recover_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	t_files			*files;
	t_files			*tmp;

	files = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (perror("opendir"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		tmp = ft_lstnew_files_dup(entry->d_name);
		if (!tmp)
		{
			perror("malloc");
			return (NULL);
		}
		ft_lst_add_back_files(&files, tmp);
	}
	closedir(dir);
	return (files);
}

char	*write_files_expand(t_files *files)
{
	t_files	*tmp;
	char	*res;
	int		lenres;

	tmp = files;
	lenres = 0;
	while (tmp)
	{
		lenres += ft_strlen(tmp->name);
		tmp = tmp->next;
	}
	res = ft_calloc(sizeof(char), lenres + 1);
	if (!res)
		return (perror("malloc"), NULL);
	tmp = files;
	while (tmp)
	{
		ft_strlcat(res, tmp->name, lenres + 1);
		tmp = tmp->next;
	}
	return (res);
}

int	creat_node_n_add_back_if_str(t_files **files, char *tmp)
{
	t_files	*new;

	if (!tmp)
		return (ft_free_lst_files_expand(files),
			perror("minishell: ft_strndup failed"), 1);
	if (tmp[0] == '\0')
		return (0);
	new = ft_lstnew_files_dup(tmp);
	if (!new)
		return (ft_free_lst_files_expand(files), 1);
	ft_lst_add_back_files(files, new);
	return (0);
}
