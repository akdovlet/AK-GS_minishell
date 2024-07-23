/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:43:26 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/23 21:27:50 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

void	print_tree_recursive(t_ast *root, int level)
{
	char	*str;

	if (!root)
	{
		print_indentation(level);
		ft_printf("NULL\n");	
		return ;
	}
	print_indentation(level);
	if (!root->type)
		str = "PIPELINE";
	else
		str = "OPERATOR";
	ft_printf("value is: %s = %s\n", str, etoa(root->value));
	if (!root->type)
	{
		print_indentation(level);
		ft_printf("%s\n", root->cmd);
	}
	print_indentation(level);
	ft_printf("left\n");
	if (root->type)
	{
		print_tree_recursive(root->left, level + 1);
	}
	print_indentation(level);
	ft_printf("right\n");
	if (root->type)
		print_tree_recursive(root->right, level + 1);
}

void	print_tree(t_ast *root)
{
	print_tree_recursive(root, 0);
}


