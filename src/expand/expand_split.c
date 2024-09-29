/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:35:52 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/27 17:52:30 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

t_files	*create_new_file_node(char *name)
{
	t_files	*new_node;

	new_node = (t_files *)malloc(sizeof(t_files));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->next = NULL;
	return (new_node);
}

// Ajout d'un élément à la fin de la liste
void	add_file_node(t_files **head, t_files *new_node)
{
	t_files	*temp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

// Fonction pour découper la chaîne et créer la liste chaînée
t_files	*ft_split_to_list(char *str)
{
	t_files	*head;
	char	*start;
	char	*word;

	head = NULL;
	if (!str)
		return (NULL);
	while (*str)
	{
		while (*str && ft_whitespace(*str))
			str++;
		if (*str)
		{
			start = str;
			while (*str && !ft_whitespace(*str))
				str++;
			word = strndup(start, str - start);
			if (!word)
				return (NULL);
			add_file_node(&head, create_new_file_node(word));
		}
	}
	return (head);
}
