/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_redir_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:59:55 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/17 15:55:07 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

	// t_ast	*ast_newcmdlist(t_ast **list, t_token **tk)
	// {
	// 	t_ast	*new;
	// 	t_ast	*tmp;
	// 	t_token *cursor;

	// 	cursor = *tk;
	// 	new = NULL;
	// 	while (*tk && (is_redirect((*tk)->type) || (*tk)->type == WORD))
	// 	{
	// 		if (is_redirect((*tk)->type))
	// 		{
	// 			ast_insert_node(&new, &cursor)
	// 		}
	// 	}
	// }
