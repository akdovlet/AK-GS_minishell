/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:35:52 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/02 13:50:27 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	ft_sep(char c, char *sep)
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

static char	*ft_strdup_split_e(char *str, int index, int nbchar)
{
	int		i;
	char	*copy;

	i = 0;
	copy = malloc((nbchar + 1) * sizeof(char));
	if (copy == NULL)
		return (0);
    if (index < 0)
        index = 0;
    while (i < nbchar)
    {
		copy[i] = str[index + i];
        i ++;
    }
    copy[i] = '\0';
	return (copy);
}

static int	ft_count_char_and_alloc_expand(char *str, char *charsep, char **tab)
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
		else
		{
			tab[m] = ft_strdup_split_e(str, i - nbchar - 1, nbchar + 1);
			if (tab[m] == NULL)
				return (0);
			m++;
			nbchar = 0;
		}
		i++;
	}
	return (m);
}

static int	ft_count_word(char *str, char *charsep)
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
		else
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
		nbword = ft_count_word(str, sep);
	tab = malloc((nbword + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (nbword > 0)
		ft_count_char_and_alloc_expand(str, sep, tab);
	tab[nbword] = 0;
	return (tab);
}


