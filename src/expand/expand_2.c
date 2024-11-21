/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:12:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/21 10:49:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"
#include "env.h"

char	*get_key(char *str, int i)
{
	int		len;
	char	*key;

	len = 0;
	while (str[i] && (is_variable(str[i]) || ft_isalnum(str[i])))
	{
		i++;
		len++;
	}
	key = malloc(sizeof(char) * (len + 1));
	return (key);
}

void	var_copy(char *str, int *i, t_data *data, t_files **lst)
{
	int		j;
	char	*key;
	char	*value;

	j = ++(*i);
	key = get_key(str, j);
	if (!key)
		return ;
	j = 0;
	while (str[*i] && (is_variable(str[*i]) || ft_isalnum(str[*i])))
		key[j++] = str[(*i)++];
	key[j] = '\0';
	value = env_get_value(data->env, key, data);
	free(key);
	if (!value)
		return ;
	value = ifs_copy(value);
	if (!value)
		return ;
	files_addback(lst, files_new(value));
}

void	send_main_lst(char *str, t_files **head)
{
	int		i;
	char	**strs;

	strs = ft_split(str, '\n');
	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		files_addback(head, files_new(strs[i]));
		i++;
	}
	free(str);
	free(strs);
}

void	expansion_routine(char *str, t_data *data, t_files **head)
{
	t_files	*sublst;
	char	*fusion;
	char	*final;

	sublst = NULL;
	fusion = expand_string(str, data, &sublst);
	if (!fusion)
		return (files_clear(&sublst));
	if (ft_find_chr_exec(fusion, '*') == 1)
	{
		fusion = expand_wildcard(fusion);
		if (ft_find_chr_exec(fusion, '\n'))
		{
			send_main_lst(fusion, head);
			return ;
		}
	}
	final = remove_quotes(fusion);
	free(fusion);
	if (!final)
		return ;
	files_addback(head, files_new(final));
	return ;
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
