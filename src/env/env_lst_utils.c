/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:50:24 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/21 16:35:45 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int find_chr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_env	*ft_last(t_env *lst)
{
	t_env	*index;

	index = lst;
	if (!lst)
		return (NULL);
	while (index->next)
		index = index->next;
	return (index);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!*(lst))
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*copy_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_strndup(str, i);
	if (!key)
		return (NULL);
	return (key);
}

t_env	*env_new(char *var)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = copy_key(var);
	if (!node->key)
		return (NULL);
	if (find_chr(var, '='))
	{
		node->value = ft_strdup(var + ft_strlen(node->key) + 1);
		if (!node->value)
			return (NULL);
	}
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

int	ft_lstsize_env(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
