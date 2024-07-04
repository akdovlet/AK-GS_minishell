/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/04 15:03:00 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

bool	is_operator(char *str)
{
	if (str[0] + str[1] == AND || str[0] + str[1] == OR || str[0] == PIPE)
		return (true);
	return (false);
}

bool	is_redirect(int c)
{
	if (c == IN || c == OUT)
		return (true);
	return (false);
}
char	*copy_op(char *str, int *i)
{
	char 	*dup;
	int		j;
	int		index;

	j = 0;
	index = *i;
	while (str[index] && is_operator(str[index]))
		j++;
	dup = malloc(sizeof(char) * j + 1);
	if (!dup)
		return (NULL);
	index = 0;
	while (str[*i] && is_operator(str[*i]))
	{
		dup[index] = str[*i];
		index++;
		(*i)++;		
	}
	dup[index] = '\0';
	return (dup);
}

void	opperator_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = ft_tokennew(NULL);
	if (!new)
		return ;
	if (str[*i] + str[*i + 1] == AND)
	{
		new->type = AND;
		if (is_operator(str[*i + 2]))
			return (bad_syntax(AND));
	}
	else if (str[*i] + str[*i + 1] == OR)
	{
		new->type = OR;
		if (is_operator(str[*i + 2]))
			return (bad_syntax(AND));
	}
	else if (str[*i] == PIPE)
	{
		new->type = PIPE;
		if (is_operator(str[*i + 1]))
			return (bad_syntax(AND));
	}
	new->value = copy_op(str, i);
	if (!new->value)
		return ;
}

void	redirect_management(char *str, int *i)
{
	t_token	*new;

	new = ft_tokennew(NULL);
	if (!new)
		return ;
	if (str[*i] == IN)
		new->type = IN;
	else if (str[*i] == OUT)
		new->type == OUT;
	
}

void	tokenize(char *line)
{
	int		i;
	t_token	*tk;

	i = 0;
	while (line[i])
	{
		if (is_opperator(&line[i]))
			opperator_management(line, &i, &tk);
		else if (is_redirect(line[i]))
			redirect_management(line, &i);
		else if (!ft_isspace(line[i]))
			word_management(line, &i, &tk);
		if (!ft_isspace(line[i]))
			word_management(line, &i, &tk);
		i++;
	}
}
