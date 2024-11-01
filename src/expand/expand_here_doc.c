/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:39:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/31 20:13:29 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "token.h"

void	regular_copy_hd(char *str, int *i, t_files **lst)
{
	int		j;
	int		len;
	char	*dup;

	j = *i;
	len = 0;
	while (str[j])
	{
		if (str[j] == '$' && (is_variable(str[j + 1]) || str[j + 1] == '?'))
			break ;
		len++;
		j++;
	}
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return ;
	j = 0;
	while (str[*i])
	{
		if (str[(*i)] == '$' && (is_variable(str[(*i) + 1]) || str[(*i) + 1] == '?'))
			break ;
		dup[j++] = str[(*i)++];
	}
	dup[j] = '\0';
	files_add_back(lst, files_new(dup));
}

char	*expand_hd(char *str, t_data *data)
{
	int		i;
	char	*fusion;
	t_files	*lst;

	i = 0;
	lst = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && is_variable(str[i + 1]))
			var_copy(str, &i, data, &lst);
		else if (str[i] == '$' && str[i + 1] == '?')
			status_copy(&i, data, &lst);
		else
			regular_copy_hd(str, &i, &lst);
	}
	fusion = files_join(&lst);
	return (fusion);
}
