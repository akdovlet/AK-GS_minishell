/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_debugging.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:43:26 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/09 19:10:59 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

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

void	ast_print_recursive(t_ast *root, int level)
{
	if (!root)
	{
		print_indentation(level);
		ft_printf("NULL\n");
		return ;
	}
	print_indentation(level);
	if (root->type == PIPELINE)
		ft_printf("PIPELINE: %s\n", root->cmd);
	else if (root->type == OPERATOR)
		ft_printf("OPERATOR: %s\n", etoa(root->operator_type));
	else if (root->type == REDIR)
		ft_printf("REDIR: %s\n", etoa(root->redir_type));
	print_indentation(level);
	ft_printf("left\n");
	if (root->type == OPERATOR)
		ast_print_recursive(root->left, level + 1);
	if (root->type == REDIR)
		ast_print_recursive(root->redir_next, level + 1);
	print_indentation(level);
	ft_printf("right\n");
	if (root->type == OPERATOR)
		ast_print_recursive(root->right, level + 1);
}

void	ast_print(t_ast *root)
{
	ast_print_recursive(root, 0);
}
