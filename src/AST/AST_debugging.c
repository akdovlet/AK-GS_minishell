/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_debugging.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:43:26 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/16 20:05:50 by akdovlet         ###   ########.fr       */
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
	if (root->type == CMD)
		ft_printf("COMMAND: %s\n", root->cmd);
	else if (root->type == OPERATOR)
		ft_printf("OPERATOR: %s\n", etoa(root->op_type));
	else if (root->type == REDIR)
	{
		ft_printf("REDIR: %s\n", etoa(root->redir_type));
		print_indentation(level);
		ft_printf("FILENAME: %s\n", root->file_name);
	}
	else if (root->type == PIPE_NODE)
		ft_printf("PIPE\n");
	else if (root->type == SUBSHELL)
		ft_printf("SUBSHELL\n");
	print_indentation(level);
	ft_printf("left\n");
	if (root->type == OPERATOR)
		ast_print_recursive(root->op_left, level + 1);
	if (root->type == REDIR)
		ast_print_recursive(root->redir_next, level + 1);
	if (root->type == PIPE_NODE)
		ast_print_recursive(root->pipe_left, level + 1);
	print_indentation(level);
	if (root->type == OPERATOR || root->type == PIPE_NODE)
	{
		ft_printf("right\n");
	}
	else
		ft_printf("next\n");
	if (root->type == OPERATOR)
		ast_print_recursive(root->op_right, level + 1);
	if (root->type == PIPE_NODE)
		ast_print_recursive(root->pipe_right, level + 1);
	if (root->type == SUBSHELL)
		ast_print_recursive(root->subshell_next, level + 1);
}

void	ast_print(t_ast *root)
{
	ast_print_recursive(root, 0);
}
