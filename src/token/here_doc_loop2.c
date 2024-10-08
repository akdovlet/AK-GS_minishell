/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_loop2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:38:19 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/08 14:19:03 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"

char	*exit_status_to_char(void)
{
	char *str;
	
	str = ft_itoa(*g_state);
	if (str)
		return (NULL);
	return (str);
}

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

int	hd_no_expand(t_token *tk)
{
	int		line_count;
	char	*line;

	line_count = 0;
	tk->value = remove_quotes(tk->value);
	while (++line_count)
	{
		line = readline("> ");
		if (!line)
			return (ft_dprintf(2, HD_ERROR, line_count, tk->value), 0);
		if (!ft_strcmp(tk->value, line))
		{
			free(line);
			break ;
		}
		write(tk->fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}
