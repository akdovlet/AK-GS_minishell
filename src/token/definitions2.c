/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:28:27 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/09 19:35:17 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

bool	is_blank(int c)
{
	if (c == SPACE || c == TAB)
		return (true);
	return (false);
}

bool	is_metacharacter(int c)
{
	if (c == NEWLINE || is_blank(c) || is_operator(c) || is_redirect(c))
		return (true);
	return (false);
}

bool	is_word(int c)
{
	if (c != 0 && !is_metacharacter(c) && !is_parenthesis(c))
		return (true);
	return (false);
}

bool	is_variable(int c)
{
	if (ft_isalpha(c) || c == '_')
		return (true);
	return (false);
}
