/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:12:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/07 19:59:47 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"
#include "env.h"

void	expand_string(char *str, t_data *data, t_files **head)
{
	int		i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '\'')
			sq_copy(str, &i, head);
		else if (str[i] == '"')
			dq_copy(str, &i, data, head);
		else if (str[i] == '$' && is_variable(str[i + 1]))
			var_copy(str, &i, data, head);
		else if (str[i] == '$' && str[i + 1] == '?')
			status_copy(&i, data, head);
		else
			regular_copy(str, &i, head);
	}
}

void	expansion_routine(char *str, t_data *data, t_files **head)
{
	t_files	*sublst;

	sublst = NULL;
	expand_string(str, data, &sublst);
	//wild_card(sublst)
	files_remove_quotes(sublst);
	files_addback_lst(head, &sublst);
}

char	**expand_cmd(char **strs, t_data *data)
{
	int		i;
	char	**cmd;
	t_files	*lst;

	i = 0;
	lst = NULL;
	while (strs[i])
	{
		expansion_routine(strs[i], data, &lst);
		i++;
	}
	ft_free(strs);
	cmd = build_cmd_array(&lst);
	return (cmd);
}

void	split_on_ifs(char *str, t_files **lst)
{
	int			i;
	char	**strs;

	i = 0;
	strs = ft_multi_split(str, "\t\n ");
	if (!strs)
		return ;
	while (strs[i])
	{
		files_addback(lst, files_new_dup(strs[i]));
		i++;
	}
	ft_free(strs);
}

void	var_copy(char *str, int *i, t_data *data, t_files **lst)
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
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return ;
	j = 0;
	while (str[*i] && is_variable(str[*i]))
		key[j++] = str[(*i)++];
	key[j] = '\0';
	value = env_get_value(data->env, key);
	free(key);
	if (!value)
		return ;
	split_on_ifs(value, lst);
}
