/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:08:47 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/12 22:53:15 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	rl_exit(void)
{
	if (g_state == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (130);
}

void	set_signal(int sig)
{
	g_state = sig;
}

int	hd_loop(char *delimiter, t_token *tk)
{
	int		line_count;
	char	*line;

	line_count = 0;
	while (++line_count)
	{
		line = readline("> ");
		if (g_state == SIGINT)
			return (free(line), 130);
		if (!line)
			return (ft_dprintf(2, HD_ERROR, line_count, delimiter), 0);
		if (!ft_strcmp(delimiter, line))
		{
			free(line);
			break ;
		}
		write(tk->fd, line, ft_strlen(line));
		write(tk->fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	here_doc(t_token *tk, int pipe_fd[2])
{
	int		tty;
	int		err;
	char	*delimiter;

	close(pipe_fd[0]);
	delimiter = remove_quotes(tk->value);
	if (!delimiter)
		return (perror("minishell: here_doc"), 1);
	tty = open("/dev/tty", O_RDWR);
	if (tty == -1)
	{
		free(delimiter);
		perror("minishell: here_doc");
		return (1);
	}
	tk->fd = pipe_fd[1];
	dup2(tty, STDIN_FILENO);
	close(tty);
	signal(SIGINT, set_signal);
	rl_event_hook = rl_exit;
	err = hd_loop(delimiter, tk);
	tk->fd = -1;
	close(pipe_fd[1]);
	free(delimiter);
	return (err);
}
