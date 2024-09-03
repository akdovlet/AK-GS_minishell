/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:59:28 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/23 16:37:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	or_check(char *str, int i)
{
	if (str[i + 1] != PIPE)
		return (PIPE);
	else if (str[i + 1] == PIPE)
		return (OR);
	return (OR * -1);
}

int	and_check(char *str, int i)
{
	if (str[i + 1] != '&')
		return ('&');
	return (AND);
}

int	out_check(char *str, int i)
{
	if (str[i] == OUT && str[i + 1] == OUT)
		return (APPEND);
	return (OUT);
}

int	in_check(char *str, int i)
{
	if (str[i] == IN && str[i + 1] == IN)
		return (HERE_DOC);
	return (IN);
}
