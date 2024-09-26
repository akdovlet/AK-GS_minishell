/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:39:17 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/26 15:23:41 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	creat_node_n_add_back(t_files **files, char *tmp)
{
	t_files	*new;

	if (!tmp)
		return (perror("minishell: ft_strndup"), 1);
	new = ft_lstnew_files(tmp);
	if (!new)
		return (1);
	ft_lst_add_back_files(files, new);
	return (0);
}

int	lst_size_files(t_files **files)
{
	t_files	*tmp;
	int		i;

	i = 0;
	tmp = *files;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

// fonction qui me copie toute ma liste chainee dans un tableau
// de chaine de caractere
char	**ft_lst_to_tab(t_files **files)
{
	t_files	*tmp;
	char	**tab;
	int		i;

	tmp = *files;
	i = lst_size_files(files);
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (perror("minishell: ft_lst_to_tab"), NULL);
	i = 0;
	tmp = *files;
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->name);
		if (!tab[i])
			return (perror("minishell: ft_strdup"), NULL);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	ft_free_lst_files_expand(files);
	return (tab);
}

char	*write_files(t_files *files)
{
	t_files	*tmp;
	char	*res;
	int		lenres;

	tmp = files;
	lenres = 0;
	while (tmp)
	{
		lenres += ft_strlen(tmp->name) + 3;
		tmp = tmp->next;
	}
	res = ft_calloc(sizeof(char), lenres + 1);
	if (!res)
		return (perror("minishell: ft_calloc"), NULL);
	tmp = files;
	while (tmp)
	{
		ft_strlcat_files(res, tmp->name, lenres + 1);
		tmp = tmp->next;
	}
	return (res);
}

void	ft_sort_alpha_files(t_files **files)
{
	t_files	*tmp;
	t_files	*tmp2;
	char	*tmp3;

	tmp = *files;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcasecmp(tmp->name, tmp2->name) > 0)
			{
				tmp3 = tmp->name;
				tmp->name = tmp2->name;
				tmp2->name = tmp3;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
