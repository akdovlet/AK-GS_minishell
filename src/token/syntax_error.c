/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:55:42 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/12 16:10:30 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

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
	else if (c == HERE_DOC)
		token = "<<";
	else if (c == IN)
		token = "<";
	else if (c == APPEND)
		token = ">>";
	else if (c == OUT)
		token = ">";
	else
		ft_dprintf(STDERR_FILENO, SYNTAX_ERR , token);
}
