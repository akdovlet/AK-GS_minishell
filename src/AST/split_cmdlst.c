/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmdlst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:32:14 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/21 17:05:20 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

int	cmdlst_len(t_cmdlist *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**cmdlst_split(t_cmdlist **lst)
{
	char	**cmd;
	int		i;
	int		len;
	
	i = 0;
	len = cmdlst_len(*lst);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (NULL);
	while (*lst)
	{
		cmd[i] = ft_strdup((*lst)->str);
		if (!cmd[i])
			return (free_array(cmd, i), NULL);
		i++;
		eat_cmdlst(lst);
	}
	cmd[i] = NULL;
	return (cmd);
}
