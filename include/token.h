/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:50 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/10 15:24:54 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

typedef	struct s_token
{
	enum e_token type;
	char	*value;
	struct	s_token	*next;
}	t_token;


/*###############################################################################
#                                  syntax.c                                     #
###############################################################################*/

// returns correct error message in case of bad syntax
void	bad_syntax(int c);


/*###############################################################################
#                                  token_check.c                                #
###############################################################################*/

bool	is_operator(int c);
bool	is_quote(int c);
bool	is_redirect(int c);
bool	is_word(int c);

/*###############################################################################
#                                  token_lst_utils.c                            #
###############################################################################*/

t_token	*ft_tokennew(char *var);
void	ft_token_add_back(t_token **lst, t_token *new);
t_token	*ft_tokennew(char *var);
void	tokenize(char *line);
void	ft_tkclear(t_token **tk);

/*###############################################################################
#                                  tokenize.c                                   #
###############################################################################*/

void	tokenize(char *line);

/*###############################################################################
#                                  type_manager.c                               #
###############################################################################*/

char	*copy_value(char *str, int *i, bool (*f)(int));
int		opperator_management(char *str, int *i, t_token **tk);
void	redirect_management(char *str, int *i, t_token **tk);

/*###############################################################################
#                                  word_manager.c                               #
###############################################################################*/

int		quote_len(char *str, int *i, int symbol);
int		quote_management(char *dup, int *j, char *str, int *i);
int		word_len(char *str, int *i);
char	*copy_word(char *str, int *i);
int		word_management(char *line, int *i, t_token **tk);

#endif
