/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:13:00 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/14 15:13:47 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"
#include "env.h"

int		sq_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		len++;
		i++;
		if (str[i] == '\'')
		{
			len++;
			break ;
		}
	}
	return (len);
}

void	sq_copy(char *str, int *i, t_files **lst)
{
	int		j;
	char	*dup;

	dup = malloc(sizeof(char) * (sq_len(str + *i) + 1));
	if (!dup)
		return (perror("minishell: sq_copy"));
	j = 0;
	while (str[*i])
	{
		dup[j++] = str[(*i)++];
		if (str[*i] == '\'')
		{
			dup[j++] = str[(*i)++];
			break ;
		}
	}
	dup[j] = '\0';
	files_add_back(lst, files_new(dup));
}

void	regular_copy(char *str, int *i, t_files **lst)
{
	int		j;
	int		len;
	char	*dup;

	j = *i;
	len = 0;
	while (str[j] && str[j] != '"' && str[j] != '\'')
	{
		if (str[j] == '$' && (is_variable(str[j + 1]) || str[j + 1] == '?'))
			break ;
		len++;
		j++;
	}
	fprintf(stderr, "len is: %d\n", len);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return ;
	j = 0;
	while (str[*i] && str[(*i)] != '"' && str[(*i)] != '\'')
	{
		if (str[(*i)] == '$' && (is_variable(str[(*i) + 1]) || str[(*i) + 1] == '?'))
			break ;
		dup[j++] = str[(*i)++];
	}
	dup[j] = '\0';
	files_add_back(lst, files_new(dup));
}

char	*expand_filename(char *str, t_data *data)
{
	int		i;
	char	*fusion;
	t_files	*lst;

	i = 0;
	lst = NULL;
	while (str[i])
	{
		fprintf(stderr, "str[%d] is: %c\n", i, str[i]);
		if (str[i] == '\'')
			sq_copy(str, &i, &lst);
		else if (str[i] == '"')
			dq_copy(str, &i, data, &lst);
		else if (str[i] == '$' && is_variable(str[i + 1]))
			var_copy(str, &i, data, &lst);
		else if (str[i] == '$' && str[i + 1] == '?')
			status_copy(&i, data, &lst);
		else
			regular_copy(str, &i, &lst);
	}
	fusion = files_join(&lst);
	return (fusion);
}
