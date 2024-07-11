/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:59:28 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/11 15:34:14 by akdovlet         ###   ########.fr       */
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

void	bad_syntax(int c)
{
	char *token;

	token = NULL;
	if (c == '|')
		token = "|";
	else if (c == '&')
		token = "&";
	else if (c == AND)
		token = "&&";
	else if (c == OR)
		token = "||";
	else if (c == PIPE)
		token = "|";
	ft_dprintf(STDERR_FILENO, SYNTAX_ERR , token);
}

void	exit_clear(t_token **tk, int status)
{
	ft_tkclear(tk);
	exit(status);
}
