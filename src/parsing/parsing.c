/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:36:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/22 20:03:46 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// t_cmdlist	*build_cmdlist(t_token **tk)
// {
// 	t_cmdlist	*lst;

// 	while (*tk && !is_logical_operator((*tk)->type) && !is_parenthesis((*tk)->type))
// 		build_cmdnode(&lst, *tk);
// 	return (lst);
// }

t_ast	*ast_newcmd(t_token **tk)
{
	t_ast	*new;

	printf("ast_newcmd\n");
	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = PIPELINE;
	new->lst = NULL;
	while (*tk && !is_logical_operator((*tk)->type))
		*tk = (*tk)->next;
	return (new);
}

t_ast	*ast_newoperator(t_type type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (perror("malloc"), NULL);
	new->type = OPERATOR;
	new->value = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_token	*next_operator(t_token *tk)
{
	while (tk)
	{
		if (is_logical_operator(tk->type))
			return (tk);
		tk = tk->next;
	}
	return (NULL);
}

t_ast	*parse_operator(t_token **tk)
{
	t_ast	*new;

	new = NULL;
	if (!(*tk) || !tk)
		return (NULL);
	if (is_logical_operator((*tk)->type))
	{
		printf("parse_operator\n");
		new = ast_newoperator((*tk)->type);
	}
	return (new);
}

t_ast	*parse_cmd(t_token **tk)
{
	t_ast	*new;

	new = NULL;
	printf("parse_cmd\n");
	if (!(*tk))
		return (NULL);
	if ((*tk)->type == PARENTHESIS_L)
	{
		printf("parenthesis\n");
		*tk = (*tk)->next;
		new = parse(tk);
		if (*tk && (*tk)->type == PARENTHESIS_R)
		{
			printf("right parenthesis\n");
			(*tk) = (*tk)->next;
		}
		return (new);
	}
	if (next_operator(*tk))
	{
		printf("next_operator\n");
		t_token *tmp = next_operator(*tk);
		printf("operator is: %s\n", etoa((tmp)->type));
		new = parse_operator(&tmp);
		new->left = ast_newcmd(tk);
		printf("after new_cmd: %s\n", etoa((*tk)->type));
		*tk = (*tk)->next;
		new->right = parse_cmd(tk);
	}
	else
		new = ast_newcmd(tk);
	return (new);
}

t_ast	*parse(t_token **tk)
{
	if (!*tk)
		return (NULL);
	return (parse_cmd(tk));
}

