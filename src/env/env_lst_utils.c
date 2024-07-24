/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:50:24 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/24 16:48:40 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

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
	if (!*(lst))
		*lst = new;
	else
		ft_last(*lst)->next = new;
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
	node->value = ft_strdup(var + ft_strlen(node->key) + 1);
	if (!node->value)
		return (NULL);
	node->both = var;
	node->next = NULL;
	return (node);
}
