/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_redir_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:59:55 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/25 18:47:49 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

void	eat_cmdlst(t_cmdlst **lst)
{
	t_cmdlst	*tmp;

	if (!(*lst) || !lst)
		return ;
	tmp = (*lst)->next;
	free((*lst)->str);
	free(*lst);
	*lst = tmp;
}

void	build_tmp_lists(t_token **tk, t_cmdlst **cmd, t_cmdlst **redir)
{
	t_type	tmp;
	int		fd;

	while (*tk && (is_redirect((*tk)->type) || (*tk)->type == WORD))
	{
		if (is_redirect((*tk)->type))
		{
			tmp = (*tk)->type;
			fd = (*tk)->next->fd;
			eat_token(tk);
			cmdlst_add_back(redir, cmdlst_new((*tk)->value, tmp, fd));
			eat_token(tk);
		}
		else if ((*tk)->type == WORD)
		{
			cmdlst_add_back(cmd, cmdlst_new((*tk)->value, CMD, 0));
			eat_token(tk);
		}
		else
			break ;
	}
}

t_ast	*ast_newcmdlist(t_token **tk)
{
	t_ast		*head;
	t_cmdlst	*cmd;
	t_cmdlst	*redir;

	cmd = NULL;
	redir = NULL;
	head = NULL;
	build_tmp_lists(tk, &cmd, &redir);
	while (redir)
	{
		redir_add_back(&head, ast_newredir(redir->type, redir->str, redir->fd));
		eat_cmdlst(&redir);
	}
	if (cmd)
		redir_add_back(&head, ast_newcmd(&cmd));
	return (head);
}

t_ast	*ast_newredir_lst(t_token **tk, t_ast *redir_next)
{
	t_ast	*new;

	new = NULL;
	if (!tk || !*tk)
		return (NULL);
	while (*tk && is_redirect((*tk)->type))
	{
		redir_add_back(&new, ast_newredir((*tk)->type, \
		(*tk)->next->value, (*tk)->next->fd));
		eat_token(tk);
		eat_token(tk);
	}
	redir_add_back(&new, redir_next);
	return (new);
}
