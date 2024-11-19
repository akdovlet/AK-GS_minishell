/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:27:54 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/19 13:39:08 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "expand.h"

char	*extract_var_name(char *str, int *i)
{
	int	j;
	int	tmp;

	j = *i + 1;
	if (str[j] == '?')
	{
		*i = j + 1;
		return (ft_strdup("?"));
	}
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	tmp = *i;
	*i = j;
	return (ft_strndup(str + tmp + 1, j - tmp - 1));
}

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

void	del_files_not_hidden(t_files **files)
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
