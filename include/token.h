/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:50 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/09 16:51:10 by akdovlet         ###   ########.fr       */
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

t_token	*ft_tokennew(char *var);
void	ft_token_add_back(t_token **lst, t_token *new);
t_token	*ft_tokennew(char *var);
void	tokenize(char *line);
void	ft_tkclear(t_token **tk);

#endif
