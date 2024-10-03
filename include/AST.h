/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:41:40 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/03 11:33:23 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"
# include "token.h"

/*#############################################################################
#                                  AST_allocation.c                           #
#############################################################################*/

t_ast		*ast_newcmd(t_cmdlst **lst);
t_ast		*ast_newop(t_ast *left, t_type type, t_ast *right);
t_ast		*ast_newredir(t_type type, char *filename, int fd);
t_ast		*ast_newpipe(t_ast *left, t_ast *right);
t_ast		*ast_newsubshell(t_ast *next);

/*#############################################################################
#                                  AST_debugging.c                            #
#############################################################################*/

void		ast_print(t_ast *root);
void		print_arrayofchar(char **str, int level);

/*#############################################################################
#                                  AST_redir_nodes.c                          #
#############################################################################*/

void		eat_cmdlst(t_cmdlst **lst);
t_ast		*ast_newcmdlist(t_token **tk);
t_ast		*ast_newredir_lst(t_token **tk, t_ast *redir_next);

/*#############################################################################
#                                  AST_redir_utils.c                          #
#############################################################################*/

void		redir_add_back(t_ast **lst, t_ast *new);

/*#############################################################################
#                                  AST_utils.c                                #
#############################################################################*/

void		next_token(t_token **tk);
void		eat_token(t_token **tk);
void		ast_free(t_ast *ast);

/*#############################################################################
#                                  AST_wait_nodes.c                           #
#############################################################################*/

int			find_subshell(t_ast	*root);
t_ast		*ast_newwait(t_ast *wait_next);

/*#############################################################################
#                                  AST.c                                      #
#############################################################################*/

t_ast		*parse(t_token **tk);
t_ast		*parse_redirect(t_token **tk);
t_ast		*parse_operator(t_token **tk);
t_ast		*parse_cmd(t_token **tk);

/*#############################################################################
#                                  cmd_list.c                                 #
#############################################################################*/

void		cmdlst_print(t_cmdlst *lst);
t_cmdlst	*cmdlst_last(t_cmdlst *lst);
void		cmdlst_add_back(t_cmdlst **lst, t_cmdlst *new);
void		cmdlst_clear(t_cmdlst **lst);
t_cmdlst	*cmdlst_new(char *value, int type, int tk);

/*#############################################################################
#                                  split_cmdlst.c                             #
#############################################################################*/

char		**cmdlst_split(t_cmdlst **lst);

#endif
