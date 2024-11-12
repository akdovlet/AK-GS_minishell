/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:56:52 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/12 19:30:44 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "minishell.h"
#include "token.h"

void	here_doc_exit(t_token **head, char *line, t_data *data, int code)
{
	token_clear(head);
	free(line);
	env_clear(&data->env);
	env_clear(&data->export);
	free(data->hardpath);
	rl_clear_history();
	exit(code);
}

int	fork_protection(int pipe_fd[2])
{
	perror("minishell: here_doc_manager");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}

int	here_doc_manager(t_token **head, char *line, t_token *tk, t_data *data)
{
	int	status;
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) == -1)
		return (perror("minishell: here document"), 1);
	pid = fork();
	if (pid == -1)
		return (fork_protection(pipe_fd));
	if (!pid)
	{
		status = here_doc(tk, pipe_fd);
		here_doc_exit(head, line, data, status);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	close(pipe_fd[1]);
	tk->fd = pipe_fd[0];
	sigaction(SIGINT, &data->sa, NULL);
	return (status);
}
