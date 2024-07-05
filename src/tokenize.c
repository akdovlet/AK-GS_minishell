/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/05 17:34:49 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "ft_dprintf.h"

bool	is_operator(int c)
{
	if (c == '&' || c == PIPE)
		return (true);
	return (false);
}


bool	is_redirect(int c)
{
	if (c == IN || c == OUT)
		return (true);
	return (false);
}

bool	is_word(int c)
{
	if (!is_operator(c) && !is_redirect(c) && !ft_isspace(c))
		return (true);
	return (false);
}

void	bad_syntax(int c)
{
	char *token;

	token = NULL;
	if (c == AND)
		token = "&&";
	else if (c == OR)
		token = "||";
	else if (c == PIPE)
		token = "|";
	ft_dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `%s'\n", token);
}

char	*copy_value(char *str, int *i, bool (*f)(int))
{
	int		j;
	char	*dup;

	j = 0;
	while (str[*i + j] && f(str[*i + j]))
		j++;
	dup = malloc(sizeof(char) * j + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (str[*i] && f(str[*i]))
	{
		dup[j] = str[*i];
		j++;
		(*i)++;
	}
	dup[j] = '\0';
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
		new->type = OR;
	else if (str[*i] == PIPE)
		new->type = PIPE;
	new->value = copy_value(str, i, is_operator);
	if (!new->value)
		return ;
	ft_token_add_back(tk, new);
}


void	redirect_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = ft_tokennew(NULL);
	if (!new)
		return ;
	if (str[*i] + str[*i + 1] == APPEND)
		new->type = APPEND;
	else if (str[*i] + str[*i + 1] == HERE_DOC)
		new->type = HERE_DOC;
	else if (str[*i] == IN)
		new->type = IN;
	else if (str[*i] == OUT)
		new->type = OUT;
	new->value = copy_value(str, i, &is_redirect);
	if (!new->value)
		return ;
	ft_token_add_back(tk, new);
}

char	*copy_word(char *str, int *i)
{
	int		j;
	char	*dup;

	j = 0;
	while (str[*i + j] && is_word(str[*i + j]))
		j++;
	dup = malloc(sizeof(char) * j + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (str[*i] && is_word(str[*i]))
	{
		dup[j] = str[*i];
		j++;
		(*i)++;
	}
	dup[j] = '\0';
	return (dup);
}

void	word_management(char *line, int *i, t_token **tk)
{
	t_token *new;

	new = ft_tokennew(NULL);
	if (!new)
		return ;
	new->type = WORD;
	new->value = copy_word(line, i);
	ft_token_add_back(tk, new);
}

void	print_token(t_token *tk)
{
	while (tk)
	{
		ft_printf("type is: %d\n", tk->type);
		ft_printf("value is: %s\n", tk->value);
		tk = tk->next;
	}
}

void	tokenize(char *line)
{
	int		i;
	t_token	*tk;

	i = 0;
	tk = NULL;
	while (line[i] && line[i] != '\n')
	{
		if (is_operator(line[i]))
			opperator_management(line, &i, &tk);
		else if (is_redirect(line[i]))
			redirect_management(line, &i, &tk);
		else if (!ft_isspace(line[i]))
			word_management(line, &i, &tk);
		i++;
	}
	print_token(tk);
}
