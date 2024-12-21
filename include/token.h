/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:50 by akdovlet          #+#    #+#             */
/*   Updated: 2024/12/21 15:10:50 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"
# define HD_ERROR "minishell: warning: here-document at \
line %d delimited by end-of-file (wanted `%s')\n"

/*#############################################################################
#                                  debugging.c                                #
#############################################################################*/

char	*etoa(t_type c);
void	print_token(t_token *tk);

/*#############################################################################
#                                  definitions2.c                             #
#############################################################################*/

bool	is_blank(int c);
bool	is_metacharacter(int c);
bool	is_word(int c);
bool	is_variable(int c);

/*#############################################################################
#                                  grammar_check.c                            #
#############################################################################*/

int		grammar_check(t_token *tk);

/*#############################################################################
#                                  here_doc_loop.c                            #
#############################################################################*/

int		here_doc(t_token *tk, int pipe_fd[2]);

/*#############################################################################
#                                  here_doc_loop2.c                           #
#############################################################################*/

int		hd_loop(char *delimiter, t_token *tk);

/*#############################################################################
#                                  here_doc_manager.c                         #
#############################################################################*/

int		here_doc_manager(t_token **head, char *line, t_token *tk, t_data *data);
char	*remove_quotes(char *str);

/*#############################################################################
#                                  definitions.c                              #
#############################################################################*/

bool	is_operator(int c);
bool	is_logical_operator(int c);
bool	is_quote(int c);
bool	is_redirect(int c);
bool	is_parenthesis(int c);

/*#############################################################################
#                                  parenthesis.c                              #
#############################################################################*/

int		parenthesis_management(char *str, int *i, t_token **token);

/*#############################################################################
#                                  syntax_error.c                             #
#############################################################################*/

void	bad_syntax3(t_token *tk);
void	bad_syntax2(char *str);
// returns correct error message in case of bad syntax
void	bad_syntax(int c);

/*#############################################################################
#                                  syntax_input.c                             #
#############################################################################*/

int		or_check(char *str, int i);
int		and_check(char *str, int i);
int		out_check(char *str, int i);
int		in_check(char *str, int i);

/*#############################################################################
#                                  syntax_order.c                             #
#############################################################################*/

int		syntax_order_check(t_token *tk);

/*#############################################################################
#                                  token_lst_utils.c                          #
#############################################################################*/

t_token	*token_new(char *var);
int		token_add_back_grammar(t_token **lst, t_token *new);
void	token_clear(t_token **tk);

/*#############################################################################
#                                  tokenize.c                                 #
#############################################################################*/

int		tokenize(char *line, t_token **tk, t_data *data);

/*#############################################################################
#                                  type_manager.c                             #
#############################################################################*/

char	*copy_value(char *str, int *i, bool (*f)(int));
int		operator_management(char *str, int *i, t_token **tk);
int		redirect_management(char *str, int *i, t_token **tk);

/*#############################################################################
#                                  word_manager.c                             #
#############################################################################*/

int		quote_len(char *str, int *i, int symbol);
int		quote_management(char *dup, int *j, char *str, int *i);
int		word_len(char *str, int *i);
char	*copy_word(char *str, int *i);
int		word_management(char *line, int *i, t_token **tk, t_data *data);

#endif
