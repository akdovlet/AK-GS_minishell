/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:06:17 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/20 17:54:26 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

// char	*etoa(t_type c)
// {
// 	if (c == WORD)
// 		return ("WORD");
// 	if (c == AND)
// 		return ("AND");
// 	if (c == OR)
// 		return ("OR");
// 	if (c == APPEND)
// 		return ("APPEND");
// 	if (c == HERE_DOC)
// 		return ("HERE_DOC");
// 	if (c == PIPE)
// 		return ("PIPE");
// 	if (c == '(')
// 		return ("PARENTHESIS_L");
// 	if (c == ')')
// 		return ("PARENTHESIS_R");
// 	if (c == S_QUOTE)
// 		return ("S_QUOTE");
// 	if (c == D_QUOTE)
// 		return ("D_QUOTE");
// 	if (c == OUT)
// 		return ("OUT");
// 	if (c == IN)
// 		return ("IN");
// 	if (c == BACKGROUND)
// 		return ("BACKGROUND");
// 	return (NULL);
// }

// void	print_token(t_token *tk)
// {
// 	while (tk)
// 	{
// 		printf("type is: %s\t", etoa(tk->type));
// 		printf("value is: %s\n", tk->value);
// 		tk = tk->next;
// 	}
// }
