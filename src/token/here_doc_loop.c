/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:08:47 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/26 11:26:41 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"

char	*find_var(char *line, int *i, t_env *env)
{
	int		index;
	int		j;
	char	*key;
	char	*value;

	(*i)++;
	index = *i;
	j = 0;
	while (line[index] && ft_isalpha(line[index++]))
		j++;
	key = malloc(sizeof(char) * j + 1);
	if (!key)
		return (NULL);
	j = 0;
	while (line[*i] && ft_isalpha(line[*i]))
	{
		key[j] = line[*i];
		j++;
		(*i)++;
	}
	key[j] = '\0';
	value = env_get_value(env, key);
	free(key);
	return (value);
}

void	cpy_to_buffer(char *value, char *buffer, int *j)
{
	int	i;

	i = 0;
	if (!value)
		return ;
	while (value[i])
	{
		buffer[*j] = value[i];
		(*j)++;
		i++;
	}
}

// cna start with underscore
char	*line_expand(char *line, t_env *env)
{
	int		i;
	int		j;
	char	*dup;
	char	*value;
	char	*buffer;

	i = 0;
	j = 0;
	if (!ft_strchr(line, '$'))
		return (ft_strdup(line));
	buffer = malloc(sizeof(char) * 4096);
	while (line[i])
	{
		if (line[i] == '$' && ft_isalpha(line[i + 1]))
		{
			value = find_var(line, &i, env);
			cpy_to_buffer(value, buffer, &j);
		}
		else if (line[i])
			buffer[j++] = line[i++];
	}
	buffer[j] = '\0';
	dup = ft_strdup(buffer);
	free(buffer);
	return (dup);
}

int	hd_expand(t_token *tk, t_env *env, int tty)
{
	int		line_count;
	char	*line;
	char	*expansion;

	line_count = 0;
	while (++line_count)
	{
		if (*g_state == 130)
			return (1);
		write(tty, "> ", 2);
		line = get_next_line(tty);
		if (*g_state == 130)
			return (free(line), 1);
		if (!line && *g_state != 130)
			return (ft_dprintf(2, HD_ERROR, line_count, tk->value), 0);
		if (hd_strcmp(tk->value, line))
			return (free(line), 0);
		expansion = line_expand(line, env);
		write(tk->fd, expansion, ft_strlen(line));
		free(line);
		free(expansion);
	}
	return (0);
}

int	here_doc(t_token *tk, t_env *env)
{
	int		pipe_fd[2];
	int		tty;
	int		err;

	err = 0;
	tty = open("/dev/tty", O_RDWR);
	if (tty == -1)
		return (ft_dprintf(2, "minishell: %s\n", strerror(errno), 0));
	if (pipe(pipe_fd) == -1)
		return (close(tty), 0);
	tk->fd = pipe_fd[1];
	*g_state = 69;
	if (ft_strchr(tk->value, '\'') || ft_strchr(tk->value, '"'))
		err = hd_no_expand(tk, tty);
	else
		err = hd_expand(tk, env, tty);
	close(pipe_fd[1]);
	close(tty);
	tk->fd = pipe_fd[0];
	if (err)
		return (0);
	return (1);
}
