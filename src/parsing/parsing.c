/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:36:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/23 22:03:42 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_ast	*ast_newcmd(t_token **tk)
{
	t_ast	*new;

	printf("ast_newcmd\n");
	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = PIPELINE;
	new->lst = NULL;
	new->cmd = ft_strdup((*tk)->value);
	*tk = (*tk)->next;
	if (*tk)
		printf("after eating5: %s\n", etoa((*tk)->type));
	while (*tk && !is_logical_operator((*tk)->type) && !is_parenthesis((*tk)->type))
	{
		*tk = (*tk)->next;
		if (*tk)
			printf("after eating4: %s\n", etoa((*tk)->type));
	}
	return (new);
}

t_ast	*build_operator(t_ast *left, t_type type, t_ast *right)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	new->type = OPERATOR;
	if (!new)
		return (NULL);
	new->left = left;
	new->value = type;
	new->right = right;
	return (new);
}

t_ast	*parse_cmd(t_token **tk)
{
	t_ast	*new;

	new = NULL;
	if (!(*tk) || !tk)
		return (NULL);
	if (!is_logical_operator((*tk)->type) && !is_parenthesis((*tk)->type))
		new = ast_newcmd(tk);	
	else if (is_parenthesis((*tk)->type))
	{
		*tk = (*tk)->next;
		printf("after eating3: %s\n", etoa((*tk)->type));
		new = parse_operator(tk);
		if ((*tk)->type == PARENTHESIS_R)
		{
			*tk = (*tk)->next;
			if (*tk)
				printf("after eating2: %s\n", etoa((*tk)->type));	
		}
	}
	return (new);
}


t_ast	*parse_operator(t_token **tk)
{
	t_ast	*new;
	t_type	tmp;

	if (!(*tk) || !tk)
		return (NULL);
	new = parse_cmd(tk);
	while (*tk && is_logical_operator((*tk)->type))
	{
		tmp = (*tk)->type;
		*tk = (*tk)->next;
		if (*tk)
			printf("after eating1: %s\n", etoa((*tk)->type));
		new = build_operator(new, tmp, parse_cmd(tk));
	}
	return (new);
}

t_ast	*parse(t_token **tk)
{
	if (!*tk)
		return (NULL);
	return (parse_operator(tk));
}

