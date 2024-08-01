/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:35:52 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/01 14:58:15 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	ft_sep(char c, char *sep)
{
	int	i;

	i = 0;
	if (sep == NULL)
		return (0);
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup_split(char *str, int index, int nbchar)
{
	int		i;
	char	*copy;

	i = 0;
	copy = malloc((nbchar + 1) * sizeof(char));
	if (copy == NULL)
		return (0);
	while (i < nbchar)
		copy[i++] = str[index++];
	copy[i] = '\0';
	return (copy);
}

int	ft_count_char_and_alloc(char *str, char *charsep, char **tab)
{
	int	m;
	int	nbchar;
	int	i;

	i = 0;
	m = 0;
	nbchar = 0;
	while (i == 0 || str[i - 1])
	{
		if (str[i] && ft_sep(str[i], charsep) == 0)
			nbchar++;
		else if (nbchar > 0)
		{
			tab[m] = ft_strdup_split(str, i - nbchar, nbchar);
			if (tab[m] == NULL)
				return (0);
			m++;
			nbchar = 0;
		}
		i++;
	}
	return (m);
}

int	ft_count_word(char *str, char *charsep)
{
	int	m;
	int	nbchar;
	int	i;

	i = 0;
	m = 0;
	nbchar = 0;
	while (i == 0 || str[i - 1])
	{
		if (str[i] && ft_sep(str[i], charsep) == 0)
			nbchar++;
		else if (nbchar > 0)
		{
			m++;
			nbchar = 0;
		}
		i++;
	}
	return (m);
}

char **ft_split_expand(char *str, char *sep)
{
	char	**tab;
	int		nbword;

	if (str == NULL || str[0] == '\0')
		nbword = 0;
	else
		nbword = ft_count_word(str, charset);
	tab = malloc((nbword + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (nbword > 0)
		ft_count_char_and_alloc(str, charset, tab);
	tab[nbword] = 0;
	return (tab);
}


