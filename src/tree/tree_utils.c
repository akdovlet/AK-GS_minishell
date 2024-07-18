/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:43:26 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/18 15:44:30 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*tree_node_init(int value)
{
	t_tree	*new;
	
	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->value = value;
	return (new);
}

void	print_indentation(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		ft_printf("\t");
		i++;
	}
}

void	print_tree_recursive(t_tree *root, int level)
{
	if (!root)
	{
		print_indentation(level);
		ft_printf("Empty\n");	
		return ;
	}
	print_indentation(level);
	ft_printf("value is: %d\n", root->value);
	print_indentation(level);
	ft_printf("left\n");
	print_tree_recursive(root->left, level + 1);
	print_indentation(level + 1);
	ft_printf("right\n");
	print_tree_recursive(root->right, level + 1);
}

void	print_tree(t_tree *root)
{
	print_tree_recursive(root, 0);
}


