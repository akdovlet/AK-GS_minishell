/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_files_double_quote.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:01:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/14 13:17:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"
#include "env.h"

int		dq_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$' && (is_variable(str[(i) + 1]) ||\
			(str[i] == '$' && str[i + 1] == '?')))
			break ;
		len++;
		i++;
		if (str[i] == '"')
		{
			len++;
			break ;
		}
	}
	return (len);
}

void	dq_copy_tmp(char *str, int *i, t_files **tmp)
{
	int		j;
	int		len;
	char	*dup;

	j = 0;
	len = dq_len(str + *i);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return ;
	while (str[*i])
	{
		if ((str[*i] == '$' && is_variable(str[(*i) + 1])) ||\
			(str[*i] == '$' && str[(*i) + 1] == '?'))
			break ;
		dup[j++] = str[(*i)++];
		if (str[*i] == '"')
		{
			dup[j++] = str[(*i)++];
			break ;
		}
	}
	dup[j] = '\0';
	files_add_back(tmp, files_new(dup));
}

void	dq_copy(char *str, int *i, t_data *data, t_files **lst)
{
	char	*fusion;
	t_files	*tmp_lst;

	tmp_lst = NULL;
	while (str[*i])
	{
		if (str[*i] == '$' && is_variable(str[(*i) + 1]))
			var_copy(str, i, data, &tmp_lst);
		else if (str[*i] == '$' && str[(*i) + 1] == '?')
			status_copy(i, data, &tmp_lst);
		else
			dq_copy_tmp(str, i, &tmp_lst);
	}
	fusion = files_join(&tmp_lst);
	if (!fusion)
		return ;
	files_add_back(lst, files_new(fusion));
	if (str[*i] == '"')
		(*i)++;
}
