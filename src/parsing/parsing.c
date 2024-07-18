/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:36:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/18 15:46:54 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	peek(t_token *tk, bool *f(int))
{
	while (tk)
	{
		if (f(tk->type))
			return (tk->type);
		tk = tk->next;
	}
	return (0);
}

int	create_cmd_list(t_tree **root, t_token **tk)
{
	t_tree	*new;
	int		operator;

	operator = peek(*tk, is_logical_operator())
	new = tree_node_init(peek(*tk), is_logical_operator)
		*root = tree_node_init()
}

int	parse_input(char *line)
{
	t_token *tk;

	tk =NULL;
	if (!tokenize(line, &tk))
		return (0);
	return (1);
}
