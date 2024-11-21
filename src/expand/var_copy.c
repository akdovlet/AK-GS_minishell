/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:45:10 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/21 10:50:10 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "token.h"
#include "env.h"

void	status_copy(int *i, t_data *data, t_files **head)
{
	char	*str;

	str = ft_itoa(data->status);
	*i = (*i) + 2;
	if (!str)
		return ;
	files_addback(head, files_new(str));
}

void	var_copy_redir(char *str, int *i, t_data *data, t_files **lst)
{
	int		j;
	int		len;
	char	*key;
	char	*value;

	j = ++(*i);
	len = 0;
	while (str[j] && is_variable(str[j]))
	{
		j++;
		len++;
	}
	key = malloc(sizeof(char) * len + 1);
	if (!key)
		return ;
	j = 0;
	while (str[*i] && is_variable(str[*i]))
		key[j++] = str[(*i)++];
	key[j] = '\0';
	value = env_get_value(data->env, key, data);
	free(key);
	if (!value)
		return ;
	files_addback(lst, files_new_dup(value));
}
