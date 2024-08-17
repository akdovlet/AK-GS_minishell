/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_redir_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:59:55 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/17 23:25:06 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

void	eat_cmdlst(t_cmdlist **lst)
{
	t_cmdlist	*tmp;

	if (!(*lst) || !lst)
		return ;
	tmp = (*lst)->next;
	free((*lst)->str);
	free(*lst);
	*lst = tmp;
}

void	build_tmp_lists(t_token **tk, t_cmdlist **cmd, t_cmdlist **redir)
{
	t_type	tmp;
	
	while (*tk && (is_redirect((*tk)->type) || (*tk)->type == WORD))
	{
		if (is_redirect((*tk)->type))
		{
			tmp = (*tk)->type;
			eat_token(tk);
			cmdlst_add_back(redir, cmdlst_new((*tk)->value, tmp));
			eat_token(tk);
		}
		else if ((*tk)->type == WORD)
		{
			cmdlst_add_back(cmd, cmdlst_new((*tk)->value, CMD));
			eat_token(tk);
		}
		else
			break ;
	}
}

t_ast	*ast_newcmdlist(t_ast **list, t_token **tk)
{
	t_ast		*head;
	t_ast		*cursor;
	t_cmdlist	*cmd;
	t_cmdlist	*redir;

	cmd = NULL;
	redir = NULL;
	build_tmp_lists(tk, &cmd, &redir);
	if (redir)
	{
		cursor = ast_newredir(redir->type, redir->str);
		eat_cmdlst(&redir);
		head = cursor;
		cursor = cursor->redir_next;
	}
	else if (cmd)
	{
		cursor = ast_newcmd
	}
	while (redir)
	{
		cursor = ast_newredir(redir->type, redir->str);
		eat_cmdlst(&redir);
		cursor = cursor->redir_next;
	}
	return (head);
}
