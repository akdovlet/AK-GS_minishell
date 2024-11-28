/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:21:15 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/28 15:23:21 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"
#include "env.h"

void	files_addback_lst(t_files **main, t_files **sub)
{
	while (*sub)
	{
		files_addback_new(main, files_new_dup((*sub)->name));
		files_eat(sub);
	}
}

int	files_wordcount(t_files *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	files_remove_quotes(t_files *lst)
{
	char	*tmp;

	while (lst)
	{
		tmp = remove_quotes(lst->name);
		free(lst->name);
		lst->name = tmp;
		lst = lst->next;
	}
}

char	**build_cmd_array(t_files **head)
{
	int		i;
	int		len;
	char	**strs;

	i = 0;
	if (!head || !*head)
		return (NULL);
	len = files_wordcount(*head);
	if (!len)
		return (NULL);
	strs = malloc(sizeof(char *) * (len + 1));
	if (!strs)
		return (files_clear(head), NULL);
	while (*head)
	{
		strs[i] = ft_strdup((*head)->name);
		if (!strs[i])
			return (files_clear(head), ft_free(strs), NULL);
		files_eat(head);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
