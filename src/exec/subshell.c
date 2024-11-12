/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:20:00 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/12 18:35:51 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	subshell_child(t_ast *ast, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	data->status = exec_recursion(ast->subshell_next, data);
	clear_exit(data, data->status);
}

int	subshell_node(t_ast *ast, t_data *data)
{
	int		status;
	pid_t	pid;

	data->fork = true;
	pid = fork();
	if (pid < 0)
		return (perror("minishell: subshell_node"), 1);
	if (!pid)
		subshell_child(ast, data);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			data->status = 128 + WTERMSIG(status);
		else
			data->status = WEXITSTATUS(status);
	}
	sigaction(SIGINT, &data->sa, NULL);
	data->fork = false;
	return (data->status);
}
