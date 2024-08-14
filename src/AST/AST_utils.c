/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:42:52 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/14 18:15:19 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void	next_token(t_token **tk)
{
	fprintf(stderr, "current token: %s\t", etoa((*tk)->type));
	fprintf(stderr, "current value: %s\n", (*tk)->value);
	if (!(*tk) || !tk)
		return ;
	*tk = (*tk)->next;
}
