/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:50 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/23 11:41:52 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

/*###############################################################################
#                                  debugging.c                                  #
###############################################################################*/

char	*etoa(t_type c);
void	print_token(t_token *tk);

/*###############################################################################
#                                  definitions2.c                               #
###############################################################################*/

bool	is_blank(int c);
bool	is_metacharacter(int c);
bool	is_word(int c);

/*###############################################################################
#                                  definitions.c                                #
###############################################################################*/

bool	is_operator(int c);
bool	is_logical_operator(int c);
bool	is_quote(int c);
bool	is_redirect(int c);
bool	is_parenthesis(int c);

/*###############################################################################
#                                  parenthesis.c                               #
###############################################################################*/

int		parenthesis_count(char *str, int i);
int		parenthesis_management(char *str, int *i, t_token **token);

/*###############################################################################
#                                  syntax_error.c                               #
###############################################################################*/

void	bad_syntax2(char *str);
// returns correct error message in case of bad syntax
void	bad_syntax(int c);

/*###############################################################################
#                                  syntax_input.c                               #
###############################################################################*/

int		or_check(char *str, int i);
int		and_check(char *str, int i);
int		out_check(char *str, int i);
int		in_check(char *str, int i);

/*###############################################################################
#                                  syntax_order.c                               #
###############################################################################*/

int		syntax_order_check(t_token *tk);

/*###############################################################################
#                                  token_lst_utils.c                            #
###############################################################################*/

t_token	*ft_tokennew(char *var);
void	ft_token_add_back(t_token **lst, t_token *new);
t_token	*ft_tokennew(char *var);
void	ft_tkclear(t_token **tk);

/*###############################################################################
#                                  tokenize.c                                   #
###############################################################################*/

int		tokenize(char *line, t_token **tk);
void	print_token(t_token *tk);

/*###############################################################################
#                                  type_manager.c                               #
###############################################################################*/

char	*copy_value(char *str, int *i, bool (*f)(int));
int		opperator_management(char *str, int *i, t_token **tk);
int		redirect_management(char *str, int *i, t_token **tk);

/*###############################################################################
#                                  word_manager.c                               #
###############################################################################*/

int		quote_len(char *str, int *i, int symbol);
int		quote_management(char *dup, int *j, char *str, int *i);
int		word_len(char *str, int *i);
char	*copy_word(char *str, int *i);
int		word_management(char *line, int *i, t_token **tk);

#endif
