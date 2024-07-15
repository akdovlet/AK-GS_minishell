/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:28:27 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/15 10:52:39 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

bool	is_metacharacter(int c)
{
	if (c == SPACE || c == TAB || c == NEWLINE \
		|| is_operator(c) || is_redirect(c))
		return (true);
	return (false);
}

bool	is_word(int c)
{
	if (c != 0 && !is_metacharacter(c) \
		&& !is_parenthesis(c))
		return (true);
	return (false);
}
