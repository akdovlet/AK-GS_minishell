/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:20:00 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/10 10:53:11 by akdovlet         ###   ########.fr       */
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
        fdlst_close_in_child(data->fdlst);
        data->status = exec_recursion(ast->subshell_next, data);
        exit(data->status);
    }
    else
    {
        waitpid(pid, &status, 0);
		data->status = WEXITSTATUS(status);
    }
    return (0);
}
