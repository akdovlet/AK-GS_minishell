/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:59:28 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/12 15:55:32 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	or_check(char *str, int i)
{
	if (!is_operator(str[i + 1]))
		return (PIPE);
	if (str[i + 1] != '|')
		return (PIPE * -1);
	if (is_operator(str[i + 2]))
		return (OR * -1);
	return (OR);
}

int	and_check(char *str, int i)
{
	if (str[i + 1] != '&')
		return ('&' * -1);
	if (is_operator(str[i + 2]))
		return (AND * -1);
	return (AND);
}

int	out_check(char *str, int i)
{
	if (str[i] == OUT && str[i + 1] == OUT)
	{
		if (is_redirect(str[i + 2]))
			return (APPEND * -1);
		return (APPEND);
	}
	if (str[i] == OUT && is_redirect(str[i + 1]))
		return (OUT * -1);
	return (OUT);
}

int	in_check(char *str, int i)
{
	if (str[i] == IN && str[i + 1] == IN)
	{
		if (is_redirect(str[i + 2]))
			return (HERE_DOC * -1);
		return (HERE_DOC);
	}
	if (str[i] == IN && is_redirect(str[i + 1]))
		return (IN * -1);
	return (IN);
}
