/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:20:00 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/20 18:06:26 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	subshell_child(t_ast *ast, t_data *data)
{
	data->status = exec_recursion(ast->subshell_next, data);
	fdlst_close_in_child(data->fdlst);
	clear_exit(data, data->status);
}

int	subshell_node(t_ast *ast, t_data *data)
{
	pid_t		pid;
	t_pidlst	*new;

	data->fork = true;
	pid = fork();
	if (pid < 0)
		return (perror("minishell: subshell_node"), 1);
	if (!pid)
		subshell_child(ast, data);
	else
	{
		signal(SIGINT, SIG_IGN);
		new = ft_lstnew_pidlst(pid);
		if (!new)
			return (1);
		ft_lstadd_back_pidlst(&data->pidlst, new);
	}
	data->fork = false;
	return (data->status);
}
