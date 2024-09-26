/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:13:00 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/26 12:45:16 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

char	*expand_filename(char *str, t_env *env)
{
	int	i;
	int	j;
	char	*tmp;
	char	*buffer;

	i = 0;
	j = 0;
	buffer = malloc(sizeof(char) * 4096);
	if (!buffer)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			tmp = sg_copy(str, i, buffer, j);
			cpy_to_buffer(tmp, buffer, j);
		}
		if (str[i] == '"')
			db_copy()
	}
}
