/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:51:53 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/09 19:53:13 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"
#include "env.h"

int	is_ifs(char c)
{
	if (c == '\t' || c =='\n' || c == ' ')
		return (1);
	return (0);
}

int	ifs_countword(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && !is_ifs(str[i]))
		{
			count++;
			while (str[i] && !is_ifs(str[i]))
				i++;
		}
		else
			i++;
	}
	return (count);
}

int	ifs_len(char *str, int word_count)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] && !is_ifs(str[i]))
		{
			j++;
			while (str[i] && !is_ifs(str[i]))
			{
				len++;
				i++;
			}
			if (j < word_count)
				len++;
		}
		else
			i++;
	}
	fprintf(stderr, "ifs_len is: %d\n", len);
	return (len);
}

char	*ifs_copy(char *str)
{
	int		i;
	int		j;
	int		word_count;
	char	*cpy;

	i = 0;
	j = 0;
	word_count = ifs_countword(str);
	if (!word_count)
		return (NULL);
	cpy = malloc(sizeof(char) * (ifs_len(str, word_count) + 1));
	if (!cpy)
		return (NULL);
	while (str[i])
	{
		if (str[i] && !is_ifs(str[i]))
		{
			word_count--;
			while (str[i] && !is_ifs(str[i]))
				cpy[j++] = str[i++];
			if (word_count > 0)
				cpy[j++] = str[i++];
		}
		else
			i++;
	}
	cpy[j] = '\0';
	return (cpy); 
}
