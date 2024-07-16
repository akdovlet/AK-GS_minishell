/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:46:28 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/16 15:11:11 by akdovlet         ###   ########.fr       */
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
			return (bad_syntax(tk->type), 0);
		if (is_redirect(tk->type) && tk->next->type != WORD)
			return (bad_syntax(tk->next->type), 0);
		if (is_parenthesis(tk->type) && is_operator(tk->next->type))
			return (bad_syntax(tk->next->type), 0);
		tk = tk->next;
	}
	if (tk->next == NULL && (is_redirect(tk->type) || is_operator(tk->type)))
		return (bad_syntax(tk->type), 0);
	printf("Syntax order done\n");
	return (1);
}
