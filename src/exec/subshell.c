/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:20:00 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/26 16:04:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_subshell(t_ast *ast, t_data *data)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
        return (perror("Fork failed\n"), 1);
    else if(!pid)
    {
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
        fdlst_close_in_child(data->fdlst);
        data->status = exec_recursion(ast->subshell_next, data);
        exit(data->status);
    }
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
    return (data->status);
}
