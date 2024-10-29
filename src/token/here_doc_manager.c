/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:56:52 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/29 17:08:43 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int	redir_quote_len(char *str, int *i, int symbol)
{
	int	len;

	len = 0;
	(*i)++;
	while (str[*i] && str[*i] != symbol)
	{
		len++;
		(*i)++;
	}
	(*i)++;
	return (len);
}

int	redir_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] && is_quote(str[i]))
			len += redir_quote_len(str, &i, str[i]);
		else if (str[i])
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	redir_quote_manager(char *dup, char *str, int *i, int *j)
{
	int	symbol;

	symbol = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != symbol)
	{
		dup[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

char	*remove_quotes(char *str)
{
	char	*dup;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (redir_len(str) + 1));
	if (!dup)
		return (NULL);
	while (str[i])
	{
		if (str[i] && is_quote(str[i]))
			redir_quote_manager(dup, str, &i, &j);
		else
			dup[j++] = str[i++];
	}
	dup[j] = '\0';
	return (dup);
}

int	here_doc_manager(t_token *tk, t_data *data)
{
	int		status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("minishell: here document"), 1);
	status = here_doc(tk, pipe_fd);
	close(pipe_fd[1]);
	tk->fd = pipe_fd[0];
	sigaction(SIGINT, &data->sa, NULL);
	return (status);
}
