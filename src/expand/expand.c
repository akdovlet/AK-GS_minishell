/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:10:20 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/24 13:46:56 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	copy_squote(char *str, int *i, t_files **files)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while (str[j] && str[j] != '\'')
		j++;
	tmp = ft_strndup(str + *i + 1, j - *i - 1);
	if (ft_new_lst_add_back_files(files, ft_lstnew_files(tmp)))
		return (1);
	*i = j + 1;
	return (0);
}

// probleme avec cette liste chaine on strdup 2x la meme chaine
static int	copy_dquotes(char *str, int *i, t_files **files, t_data *data)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while (str[j] && str[j] != '\"')
	{
		if (str[j] == '$' && ft_isalpha(str[j + 1]))
		{
			if (creat_node_n_add_back_if_str(files, ft_strndup(str + j, *i
						- j)))
				return (1);
			if (copy_var(str, &j, files, data) == 1)
				return (1);
			*i = j - 1;
		}
		else
			j++;
	}
	tmp = ft_strndup(str + *i + 1, j - *i - 1);
	if (creat_node_n_add_back_if_str(files, tmp))
		return (1);
	*i = j + 1;
	return (0);
}

int	tri_char(char *str, int *i, t_files **files, t_data *data)
{
	if (str[*i] == '\'')
	{
		if (copy_squote(str, i, files))
			return (1);
	}
	else if (str[*i] == '\"')
	{
		if (copy_dquotes(str, i, files, data))
			return (1);
	}
	else if (str[*i] == '$')
	{
		if (copy_var(str, i, files, data) == 1)
			return (1);
	}
	return (0);
}

// probleme tout ce qui ne rentre pas dans l'une des fonctions ne va pas etre copier
// dans notre liste chainee = potentiellement reglé
int	expand_str(char *str, t_data *data, t_files **files)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '$')
		{
			if (creat_node_n_add_back_if_str(files, ft_strndup(str + j, i - j)))
				return (1);
			if (tri_char(str, &i, files, data))
				return (1);
			j = i;
		}
		else
			(i)++;
	}
	if (creat_node_n_add_back_if_str(files, ft_strndup(str + j, i - j)))
		return (1);
	return (0);
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
		return (perror("malloc"), NULL);
	i = 0;
	tmp = *files;
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->name);
		if (!tab[i])
			return (perror("malloc"), NULL);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	ft_free_lst_files_expand(files);
	return (tab);
}

char	**expand_tab_of_cmd(char **tab_cmd, t_data *data)
{
	int		i;
	t_files	*files;
	t_files	*cmd;

	i = 0;
	cmd = NULL;
	while (tab_cmd[i])
	{
		files = NULL;
		while (tab_cmd[i] && tab_cmd[i][0] == '$' && check_var(tab_cmd[i],
				data)) // modif ici
			i++;
		if (!tab_cmd[i])
			break ;
		if (expand_str(tab_cmd[i], data, &files))
			return (NULL);
		creat_node_n_add_back_if_str(&cmd, write_files_expand(files));
		if (!cmd)
			return (NULL);
		ft_free_lst_files_expand(&files);
		i++;
	}
	free_tab(tab_cmd);
	tab_cmd = ft_lst_to_tab(&cmd);
	return (tab_cmd);
}
