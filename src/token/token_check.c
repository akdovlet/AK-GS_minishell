/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:49:31 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/10 14:50:02 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(int c)
{
	if (c == '&' || c == PIPE)
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
	if (c == IN || c == OUT)
		return (true);
	return (false);
}

bool	is_word(int c)
{
	if (c != 0 && !is_operator(c) && !is_redirect(c) && !ft_isspace(c))
		return (true);
	return (false);
}