/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:49:31 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/20 14:35:11 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(int c)
{
	if (c == '&' || c == PIPE || c == AND || c == OR)
		return (true);
	return (false);
}

bool	is_logical_operator(int c)
{
	if (c == AND || c == OR)
		return (true);
	return (false);
}

bool	is_quote(int c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (true);
	return (false);
}

bool	is_redirect(int c)
{
	if (c == IN || c == OUT || c == APPEND || c == HERE_DOC)
		return (true);
	return (false);
}

bool	is_parenthesis(int c)
{
	if (c == PARENTHESIS_L || c == PARENTHESIS_R)
		return (true);
	return (false);
}
