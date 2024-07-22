/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:41:40 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/22 13:46:11 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "token.h"

/*###############################################################################
#                                  tree_utils.c                                 #
###############################################################################*/

void	print_tree(t_ast *root);


/*###############################################################################
#                                  cmd_list.c                                   #
###############################################################################*/

t_cmdlist	*new_cmdnode(void);
t_ast	*parse_cmd(t_token **tk);
t_ast	*parse_operator(t_token **tk);
t_token	*find_operator(t_token *tk);
t_ast	*parse(t_token **tk);
t_ast	*ast_newoperator(t_type type);
t_ast	*ast_newcmd(t_token **tk);

#endif
