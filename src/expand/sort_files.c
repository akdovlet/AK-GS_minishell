/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:22:33 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/19 14:23:55 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	ft_strcmp_end_start_wildcard(char *file, char *str)
{
	int	i;
	int	j;
	int	k;

	if (!file[0])
		return (false);
	i = ft_strlen(file) - 1;
	j = ft_strlen(str) - 1;
	k = 0;
	while (i - k >= 0 && j - k >= 0)
	{
		if (j - k == 0)
			return (true);
		if (str[j - k] != file[i - k])
			return (false);
		k++;
	}
	return (false);
}

int	ft_strcmp_wildcard(char *file, char *str)
{
	int	i;

	i = 0;
	while (file[i] || str[i])
	{
		if (str[i] == '*')
			return (i + 1);
		if (str[i] != file[i])
			return (0);
		i++;
	}
	return (i + 1);
}

int	ft_strcmp_recursive(char *namefile, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str[0])
		return (1);
	while (namefile[j] && !i)
	{
		i = ft_strcmp_wildcard(namefile + j, str);
		j++;
	}
	if (!i)
		return (0);
	if (ft_find_chr(str + i, '*'))
	{
		if (i == 1)
			i = ft_strcmp_recursive(namefile, str + i);
		else
			i = ft_strcmp_recursive(namefile + j + i - 1, str + i);
	}
	else
		i = ft_strcmp_end_start_wildcard(namefile, str + i);
	return (i);
}

void	ft_lstcomp_wildcard(t_files **files, char *str)
{
	t_files	*tmp;
	t_files	*tmp2;
	int		e;

	tmp = *files;
	while (tmp)
	{
		e = ft_strcmp_wildcard(tmp->name, str);
		if (e == 1)
			e = ft_strcmp_recursive(tmp->name, str + 1);
		else if (e > 1)
			e = ft_strcmp_recursive(tmp->name + e - 1, str + e);
		if (!e)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			ft_lstdelone_files(files, tmp2);
		}
		if (e > 0)
			tmp = tmp->next;
	}
}

void	ft_strlcat_files(char *dst, const char *src, size_t lenres)
{
	ft_strlcat(dst, "\n", lenres);
	ft_strlcat(dst, src, lenres);
	ft_strlcat(dst, "\n", lenres);
}
