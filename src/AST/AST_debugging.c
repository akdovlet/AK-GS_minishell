/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_debugging.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:43:26 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/19 17:15:39 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

void	print_arrayofchar(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		fprintf(stderr, "%s\n", str[i]);
		i++;
	}
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
		ft_printf("COMMAND: %s\n", root->cmd[0]);
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

// int	exec_recursion(t_ast *ast, t_data *data)
// {
// 	if (ast->type == PIPE)
// 	{
// 		ft_pipe_recursion(ast, data);
// 	}
// 	if (ast->type == CMD)
// 	{		
// 	}
// 	if (ast->type == OPERATOR)
// 	if (ast->type == REDIR)
// 	if (ast->type == SUBSHELL)
// }

// int ft_pipe_recursion(t_ast *ast, t_data *data)
// {
// 	int	fd[2];

// 	if (pipe(fd) == -1)
// 		retun (1);
// 	data->pipeline = true;
// 	data->write = fd[1];
// 	data->status = exec_recursion(ast->pipe_left, data);
// 	data->write = fd[0];
// 	data->status = exec_recursion(ast->pipe_right, data);
// 	close(fd[0]);
// 	close(fd[1]);
// 	data->pipeline = 0;
// 	return (data->status);
// }
