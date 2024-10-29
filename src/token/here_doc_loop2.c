/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_loop2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:38:19 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/29 17:08:51 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"

bool	hd_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while ((s1[++i] || s2[i]) && s2[i] != '\n')
		if (s1[i] != s2[i])
			return (false);
	if (s2[i] == '\n' && s2[i + 1] == '\0')
		if (s1[i] == '\0')
			return (true);
	return (false);
}

int	hd_loop(t_token *tk)
{
	int		line_count;
	char	*delimiter;
	char	*line;

	line_count = 0;
	delimiter = remove_quotes(tk->value);
	if (!delimiter)
		return (perror("minishell: hd_loop"), 1);
	fprintf(stderr, "delimiter: %s\n", tk->value);
	while (++line_count)
	{
		line = readline("> ");
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
	free(delimiter);
	return (0);
}
