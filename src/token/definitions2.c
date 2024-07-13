/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:28:27 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/13 14:16:29 by akdovlet         ###   ########.fr       */
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
