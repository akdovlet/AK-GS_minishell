/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:12:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/11/07 17:15:42 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "expand.h"
#include "env.h"

void	files_add_back_lst(t_files **main, t_files **sub)
{
	while (*sub)
	{
		files_addback_new(main, files_new_dup((*sub)->name));
		files_eat(sub);
	}
}

char	**expand_cmd(char **strs, t_data *data)
{
	int		i;
	char	**cmd;
	t_files	*lst;

	i = 0;
	lst = NULL;
	while (strs[i])
	{
		if (expand_string(strs[i], data, &lst))
		{
			
			return (1);
		}
	}
	return (cmd);
}

int	expansion_routine(char *str, t_data *data, t_files **head)
{
	t_files	*sublst;

	sublst = NULL;

	expand_string(str, data, sublst);
	//wild_card(sublst)
	//remove_quote(sublst);
	files_add_back_lst(head, sublst);
}

int	expand_string(char *str, t_data *data, t_files **head)
{
	int		i;
	char	*fusion;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\'')
			sq_copy(str, &i, head);
		else if (str[i] == '"')
			dq_copy(str, &i, data, head);
		else if (str[i] == '$' && is_variable(str[i + 1]))
			var_copy(str, &i, data, head);
		else if (str[i] == '$' && str[i + 1] == '?')
			status_copy(&i, data, head);
		else
			regular_copy(str, &i, head);
	}
}
