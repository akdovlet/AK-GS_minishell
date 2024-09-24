/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:08:47 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/24 19:16:05 by akdovlet         ###   ########.fr       */
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

char	*copy_upto_dollar(char *line, int *i)
{
	char	*dup;
	int		j;
	int		len;

	j = *i;
	len = 0;
	while (line[j])
	{
		len++;
		j++;
		if (!line[j] || line[j] == '$')
			break ;
	}
	dup = malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (line[*i])
	{
		dup[j] = line[*i];
		j++;
		(*i)++;
		if (!line[*i] || line[*i] == '$')
			break ;
	}
	dup[j] = '\0';
	return (dup);
}

int	find_and_expand_var(t_files **lst, char *line, int *i, t_env *env)
{
	char	*var;

	if (!line[(*i) + 1] || ft_isspace(line[(*i) + 1]))
		ft_lst_add_back_files(lst, ft_lstnew_files("$"));
	if (!ft_isalpha(line[(*i) + 1]))
	{
		var = copy_upto_dollar(line, i);
		ft_lst_add_back_files(lst, ft_lstnew_files(var));
	}
	else
		ft_lst_add_back_files(lst, ft_lstnew_files(find_var(line, i, env)));
	return (1);
}

char *join_lst(t_files **lst)
{
	int	i;
	int	j;
	char	*fusion;
	t_files	*tmp;

	tmp = *lst;
	i = 0;
	while (tmp)
	{
		i += ft_strlen(tmp->name);
		tmp = tmp->next;
	}
	fusion = malloc(sizeof(char) * i + 1);
	if (!fusion)
		return (NULL);
	j = 0;
	while (*lst)
	{
		i = 0;
		while ((*lst)->name && (*lst)->name[i])
		{
			fusion[j] = (*lst)->name[i];
			j++;
			i++;
		}
		tmp = (*lst)->next;
		free((*lst)->name);
		free(*lst);
		*lst = tmp;
	}
	return (fusion);
}

char	*hd_expand(char *line, t_env *env)
{
	int		i;
	int		j;
	char 	*dup;
	t_files	*lst;
	t_files	*new;

	i = 0;
	j = 0;
	lst = NULL;
	if (!ft_strchr(line, '$'))
		return (line);
	while (line[i])
	{
		if (line[i] == '$')
			find_and_expand_var(&lst, line, &i, env);
		new = ft_lstnew_files(copy_upto_dollar(line, &i));
		ft_lst_add_back_files(&lst, new);
	}
	dup = join_lst(&lst);
	return (dup);
}

int	here_doc_loop(t_token *tk, bool expand, t_env *env, int tty)
{
	int		line_count;
	char	*line;

	line_count = 0;
	while (++line_count)
	{
		write(tty, "> ", 2);
		line = get_next_line(tty);
		if (!line)
			return (ft_dprintf(2, HD_ERROR, line_count, tk->value), 1);
		if (!ft_strncmp(line, tk->value, ft_strlen(line) - 1))
		{
			free(line);
			break ;
		}
		if (expand)
			line = hd_expand(line, env);
		write(tk->fd, line, ft_strlen(line));
		fprintf(stderr, "%s\n", line);
		free(line);
	}
	return (1);
}

int	here_doc(t_token *tk, bool expand, t_env *env)
{
	int		pipe_fd[2];
	int		tty;
	
	tty = open("/dev/tty", O_RDWR);
	if (tty == -1)
		return (ft_dprintf(2, "minishell: %s\n", strerror(errno), 0));
	if (pipe(pipe_fd) == -1)
		return (1);
	tk->fd = pipe_fd[1];
	if (!here_doc_loop(tk, expand, env, tty))
		return (0);
	close(pipe_fd[1]);
	close(tty);
	tk->fd = pipe_fd[0];
	return (1);
}
