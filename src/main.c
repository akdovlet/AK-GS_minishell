/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/06/19 18:29:51 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*new_node(char *str)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->value = str;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// Premiere fonction: retourner list chainee avec dans chaque noeud une string,
// et un operateur. Attention aux parentheses a gerer comme un bloc. 
// echo a | grep a && echo c
void	init_tree(t_tree **root, char *str)
{
	t_tree	*tmp;

	tmp = *root;
	while (str[i] && is_operator(str[i]))
	{
		len++;
	}
	current = new_node(strndup(str, len));
	current->right
}

int main()
{
	return (0);
}
