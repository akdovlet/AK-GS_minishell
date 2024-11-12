/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:51:53 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/12 19:15:27 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "expand.h"
#include "minishell.h"
#include "token.h"

int	is_ifs(char c)
{
	if (c == '\t' || c == '\n' || c == ' ')
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
	return (len);
}

void	ifs_copy_loop(char *str, char *cpy, int word_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
}

char	*ifs_copy(char *str)
{
	int		word_count;
	char	*cpy;

	word_count = ifs_countword(str);
	if (!word_count)
		return (NULL);
	cpy = malloc(sizeof(char) * (ifs_len(str, word_count) + 1));
	if (!cpy)
		return (NULL);
	ifs_copy_loop(str, cpy, word_count);
	return (cpy);
}
