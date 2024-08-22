/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:46:28 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/22 15:24:42 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	syntax_order_check(t_token *tk)
{
	if (!tk)
		return (1);
	if (is_operator(tk->type))
		return (bad_syntax(tk->type), 0);
	while (tk->next)
	{
		if (is_operator(tk->type) && is_operator(tk->next->type))
			return (bad_syntax3(tk->next), 0);
		if (is_redirect(tk->type) && tk->next->type != WORD)
			return (bad_syntax3(tk->next), 0);
		if (tk->type == PARENTHESIS_L && is_operator(tk->next->type))
			return (bad_syntax3(tk->next), 0);
		if (is_word(tk->type) && tk->next->type == PARENTHESIS_L)
			return (bad_syntax3(tk->next), 0);
		if (tk->type == PARENTHESIS_L && tk->next->type == PARENTHESIS_R)
			return (bad_syntax3(tk->next), 0);
		if (tk->type == PARENTHESIS_R && tk->next->type == PARENTHESIS_L)
			return (bad_syntax3(tk->next), 0);
		tk = tk->next;
	}
	if (tk->next == NULL && (is_redirect(tk->type) || is_operator(tk->type)))
		return (bad_syntax(tk->type), 0);
	return (1);
}
