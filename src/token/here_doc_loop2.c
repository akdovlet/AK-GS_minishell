/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_loop2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:38:19 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/25 19:09:25 by akdovlet         ###   ########.fr       */
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

int	hd_no_expand(t_token *tk, int tty)
{
	int		line_count;
	char	*line;

	line_count = 0;
	tk->value = remove_quotes(tk->value);
	while (++line_count)
	{
		write(tty, "> ", 2);
		line = get_next_line(tty);
		if (!line)
			return (ft_dprintf(2, HD_ERROR, line_count, tk->value), 1);
		if (*g_state == 130)
			return (free(line), 1);
		if (hd_strcmp(tk->value, line))
		{
			free(line);
			break ;
		}
		write(tk->fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}
