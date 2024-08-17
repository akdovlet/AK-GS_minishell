/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:41:40 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/17 23:30:13 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AST_H
# define AST_H

# include "minishell.h"
# include "token.h"

/*###############################################################################
#                                  AST_allocation.c                             #
###############################################################################*/

t_ast	*ast_newcmd(t_cmdlist **lst);
t_ast	*ast_newop(t_ast *left, t_type type, t_ast *right);
t_ast	*ast_newredir(t_type type, char *filename);
t_ast	*ast_newredir_push_root(t_ast *redir_next, t_type type, char *filename);
t_ast	*ast_newpipe(t_ast *left, t_ast *right);
t_ast	*ast_newsubshell(t_ast *next);

/*###############################################################################
#                                  AST_debugging.c                              #
###############################################################################*/

void	ast_print(t_ast *root);

/*###############################################################################
#                                  AST_utils.c                                  #
###############################################################################*/

void	next_token(t_token **tk);
void	eat_token(t_token **tk);

/*###############################################################################
#                                  AST.c                                        #
###############################################################################*/

t_ast	*parse(t_token **tk);
t_ast	*parse_redirect(t_token **tk);
t_ast	*parse_operator(t_token **tk);
t_ast	*parse_cmd(t_token **tk);

/*###############################################################################
#                                  cmd_list.c                                   #
###############################################################################*/

t_cmdlist	*cmdlst_last(t_cmdlist *lst);
void		cmdlst_add_back(t_cmdlist **lst, t_cmdlist *new);
void		cmdlst_clear(t_cmdlist **lst);
t_cmdlist	*cmdlst_new(char *value, t_type type);


#endif
