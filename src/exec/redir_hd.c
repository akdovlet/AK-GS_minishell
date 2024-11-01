/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:36:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/10/31 20:02:29 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

void	expand_content_here_document(t_ast *ast, t_data *data)
{
	char	*line;
	char	*expand;
	int		tmp_pipe[2];

	pipe(tmp_pipe);
	while (1)
	{
		line = get_next_line(ast->redir_fd);
		if (!line)
			break ;
		expand = expand_hd(line, data);
		write(tmp_pipe[1], expand, ft_strlen(expand));
		free(line);
		free(expand);
	}
	close(ast->redir_fd);
	ast->redir_fd = tmp_pipe[0];
	close(tmp_pipe[1]);
}

int	redir_hd(t_ast *ast, t_data *data)
{
	if (!ft_strchr(ast->redir_filename, '\'') && !ft_strchr(ast->redir_filename, '"'))
		expand_content_here_document(ast, data);
	if (dup2(ast->redir_fd, STDIN_FILENO) == -1)
		return (ft_dprintf(2, "minishell: %s\n", strerror(errno)), 1);
	close(ast->redir_fd);
	return (0);
}
