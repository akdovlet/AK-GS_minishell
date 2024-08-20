/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:42:52 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/20 13:33:29 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void	eat_token(t_token **tk)
{
	t_token	*tmp;

	if (!(*tk) || !tk)
		return ;
	tmp = (*tk)->next;
	free((*tk)->value);
	free(*tk);
	*tk = tmp;
}

void	ast_free(t_ast *ast)
{
	if (!ast)
		return;
	if (ast->type == CMD)
	{
		ft_free(ast->cmd);
		free(ast);
	}
	else if (ast->type == OPERATOR)
	{
		ast_free(ast->op_left);
		ast_free(ast->op_right);
		free(ast);
	}
	else if (ast->type == REDIR)
	{
		ast_free(ast->redir_next);
		free(ast->redir_filename);
		free(ast);
	}
	else if (ast->type == PIPE_NODE)
	{
		ast_free(ast->pipe_left);
		ast_free(ast->pipe_right);
		free(ast);
	}
	else if (ast->type == SUBSHELL)
	{
		ast_free(ast->subshell_next);
		free(ast);
	}
}

void	next_token(t_token **tk)
{
	if (!(*tk) || !tk)
		return ;
	*tk = (*tk)->next;
}