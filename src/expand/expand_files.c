/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:13:00 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/27 19:55:31 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"
#include "env.h"

void	files_eat(t_files **node)
{
	t_files	*tmp;

	if (!*node || !node)
		return ;
	tmp = (*node)->next;
	if ((*node)->name)
		free((*node)->name);
	free(*node);
	*node = tmp;
}

int	files_len(t_files *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		if (lst->name)
			len += ft_strlen(lst->name);
		lst = lst->next;
	}
	return (len);
}

char	*files_join(t_files **lst)
{
	int		len;
	int		i;
	int		j;
	char	*fusion;

	if (!*lst || !lst)
		return (NULL);
	i = 0;
	len = files_len(*lst);
	fusion = malloc(sizeof(char) * (len + 1));
	while (*lst)
	{
		if ((*lst)->name)
		{
			j = 0;
			while ((*lst)->name[j])
				fusion[i++] = (*lst)->name[j++];
		}
		files_eat(lst);
	}
	return (fusion);
}

void	sg_copy(char *str, int *i, t_files **lst)
{
	int		j;
	int		len;
	char	*dup;

	len = 0;
	j = ++(*i);
	while (str[j] && str[j] != '\'')
	{
		len++;
		j++;
	}
	dup = malloc(sizeof(char) * len + 1);
	if (!dup)
		return ;
	j = 0;
	while (str[*i] && str[*i] != '\'')
		dup[j++] = str[(*i)++];
	(*i)++;
	dup[j] = '\0';
	ft_lst_add_back_files(lst, ft_lstnew_files(dup));
}

void	db_copy_tmp(char *str, int *i, t_files **tmp)
{
	int		j;
	int		len;
	char	*dup;

	j = *i;
	len = 0;
	while (str[j] && str[j] != '"')
	{
		if (str[*i] == '$' && is_variable(str[(*i) + 1]))
			break ;
		len++;
		j++;
	}
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return ;
	j = 0;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && is_variable(str[(*i) + 1]))
			break ;
		dup[j++] = str[(*i)++];
	}
	dup[j] = '\0';
	ft_lst_add_back_files(tmp, ft_lstnew_files(dup));
}

void	var_copy(char *str, int *i, t_env *env, t_files **lst)
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
	value = env_get_value(env, key);
	if (!value)
		return ;
	ft_lst_add_back_files(lst, ft_lstnew_files_dup(value));
}

void	db_copy(char *str, int *i, t_env *env, t_files **lst)
{
	int		j;
	char	*fusion;
	t_files	*tmp_lst;

	j = 0;
	(*i)++;
	tmp_lst = NULL;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && is_variable(str[(*i) + 1]))
			var_copy(str, i, env, &tmp_lst);
		else
			db_copy_tmp(str, i, &tmp_lst);
	}
	fusion = files_join(&tmp_lst);
	if (!fusion)
		return ;
	ft_lst_add_back_files(lst, ft_lstnew_files(fusion));
	if (str[*i] == '"')
		(*i)++;
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
		if (str[j] == '$' && is_variable(str[j + 1]))
			break ;
		len++;
		j++;
	}
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return ;
	j = 0;
	while (str[*i] && str[j] != '"' && str[j] != '\'')
	{
		if (str[j] == '$' && is_variable(str[j + 1]))
			break ;
		dup[j++] = str[(*i)++];
	}
	dup[j] = '\0';
	ft_lst_add_back_files(lst, ft_lstnew_files(dup));
}

char	*expand_filename(char *str, t_env *env)
{
	int		i;
	int		j;
	char	*fusion;
	t_files	*lst;

	i = 0;
	j = 0;
	lst = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			sg_copy(str, &i, &lst);
		else if (str[i] == '"')
			db_copy(str, &i, env, &lst);
		else if (str[i] == '$' && is_variable(str[i + 1]))
			var_copy(str, &i, env, &lst);
		else
			regular_copy(str, &i, &lst);
	}
	fusion = files_join(&lst);
	free(str);
	return (fusion);
}
