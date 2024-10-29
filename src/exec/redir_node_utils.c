/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_node_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:35:27 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/29 16:49:25 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include "token.h"
#include "expand.h"

int redir_expand(t_ast *ast, t_data *data)
{
	char	*expansion;

	expansion = expand_filename(ast->redir_filename, data);
	expansion = remove_quotes(expansion);
	if (!expansion)
		return (ft_dprintf(2, "minishell: %s: ambiguous redirect\n", ast->redir_filename), 1);
	free(ast->redir_filename);
	ast->redir_filename = expansion;
	return (0);
}