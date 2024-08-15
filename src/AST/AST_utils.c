/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:42:52 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/15 13:38:29 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void	eat_token(t_token **tk)
{
	t_token	*tmp;

	if (!(*tk) || !tk)
		return ;
	tmp = (*tk)->next;
	free((*tk)->value);
	free(*tk);
	*tk = tmp;
	if (tk && *tk)
	{
		fprintf(stderr, "current token: %s\t", etoa((*tk)->type));
		fprintf(stderr, "current value: %s\n", (*tk)->value);		
	}
}

void	next_token(t_token **tk)
{
	fprintf(stderr, "current token: %s\t", etoa((*tk)->type));
	fprintf(stderr, "current value: %s\n", (*tk)->value);
	if (!(*tk) || !tk)
		return ;
	*tk = (*tk)->next;
}
