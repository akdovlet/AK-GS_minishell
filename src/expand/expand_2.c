/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:12:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/08 19:04:24 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"
#include "env.h"

void	split_on_ifs(t_files **lst, t_files **sublst);

int	is_ifs(char c)
{
	if (c == '\t' || c =='\n' || c == ' ')
		return (1);
	return (0);
}

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
	t_files	*sublst2;

	sublst = NULL;
	sublst2 = NULL;
	expand_string(str, data, &sublst);
	split_on_ifs(&sublst, &sublst2);
	//wild_card(sublst)
	files_remove_quotes(sublst2);
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

void	split_on_ifs_dq(char *str, int *i, char *buffer, int *j)
{
	while (str[*i])
	{
		buffer[(*j)++] = str[(*i)++];
		if (str[*i] == '"')
		{
			buffer[(*j)++] = str[(*i)++];
			break ;
		}
	}
}

void	split_on_ifs_sq(char *str, int *i, char *buffer, int *j)
{
	while (str[*i])
	{
		buffer[(*j)++] = str[(*i)++];
		if (str[*i] == '\'')
		{
			buffer[(*j)++] = str[(*i)++];
			break ;
		}
	}
}

void	split_on_ifs_cpy(char *str, int *i, char *buffer, int *j)
{
	if (str[*i] && is_ifs(str[(*i)++]))
	{
		buffer[*j] = '\0';
		*j = 0;
		while (str[*i] && is_ifs(str[*i]))
			(*i)++;	
	}
}

void	check_if_content(char *str, t_files **lst, int j)
{
	int	i;

	i = 0;
	if (j != 0)
	{
		while (str[i])
		{
			if (!is_ifs(str[i]))
			{
				files_addback(lst, files_new_dup(str));
				break ;
			}
			i++;
		}		
	}
}

void	split_on_ifs(t_files **lst, t_files **sublst)
{
	int		len;
	int		i;
	int		j;
	char	*buffer;

	j = 0;
	len = files_len(*lst);
	buffer = malloc(sizeof(char) * (len + 1));
	while (*lst)
	{
		i = 0;
		while ((*lst)->name[i])
		{
			if ((*lst)->name[i] == '"')
				split_on_ifs_dq((*lst)->name, &i, buffer, &j);
			else if ((*lst)->name[i] == '\'')
				split_on_ifs_sq((*lst)->name, &i, buffer, &j);
			else if (!(*lst)->name[i] || is_ifs((*lst)->name[i]))
			{
				split_on_ifs_cpy((*lst)->name, &i, buffer, &j);
				check_if_content(buffer, sublst, j);
				break ;
			}
			else
				buffer[j++] = (*lst)->name[i++];
		}
		files_eat(lst);
	}
	if (j != 0)
	{
		buffer[j] = '\0';
		files_addback(lst, files_new_dup(buffer));
	}
	free(buffer);
}

int	find_ifs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
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
	files_addback(lst, files_new_dup(value));
}
