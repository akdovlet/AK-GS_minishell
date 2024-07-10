/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:45 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/10 14:42:34 by akdovlet         ###   ########.fr       */
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

bool	is_quote(int c)
{
	if (c == S_QUOTE || c == D_QUOTE)
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
	if (c != 0 && !is_operator(c) && !is_redirect(c) && !ft_isspace(c))
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

int	opperator_management(char *str, int *i, t_token **tk)
{
	t_token	*new;

	new = ft_tokennew(NULL);
	if (!new)
		return (0);
	if (str[*i] + str[*i + 1] == AND)
	{
		new->type = AND;
		if (is_operator(str[*i + 2]))
		{
			bad_syntax(AND);
			ft_tkclear(tk);
			return (0);
		}
	}
	else if (str[*i] + str[*i + 1] == OR)
		new->type = OR;
	else if (str[*i] == PIPE)
		new->type = PIPE;
	new->value = copy_value(str, i, is_operator);
	if (!new->value)
		return (0);
	ft_token_add_back(tk, new);
	return (1);
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
	new->value = copy_value(str, i, is_redirect);
	if (!new->value)
		return ;
	ft_token_add_back(tk, new);
}

int	quote_len(char *str, int *i, int symbol)
{
	int	len;

	len = 1;
	(*i)++;
	while (str[*i] && str[*i] != '\n' && str[*i] != symbol	)
	{
		len++;
		(*i)++;
	}
	return (len);
}

int	word_len(char *str, int *i)
{
	int	len;
	int	index;

	len = 0;
	index = *i;
	while (str[index] && str[index] != '\n')
	{
		if (is_quote(str[index]))
		{
			len += quote_len(str, &index, str[index]);
		}
		if (!is_word(str[index]))
			break ;
		else
		{
			(index)++;
			len++;
		}
	}
	return (len);
}

int		quote_management(char *dup, int *j, char *str, int *i)
{
	char	symbol;

	symbol = str[*i];
	dup[(*j)++] = str[(*i)++];
	while (str[*i] && str[*i] != '\n' && str[*i] != symbol)
	{
		dup[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
	if (str[*i] != symbol)
	{
		ft_dprintf(STDERR_FILENO, "minishell: unexpected newline while looking for matching `%c'\n", symbol);
	}
		return (0);
	dup[(*j)++] = str[(*i)++];
	return (1);
}

bool	find_symbol(char *str, int symbol)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == symbol)
			return (true);
		i++;
	}
	return (false);
}
char	*copy_word(char *str, int *i)
{
	int		j;
	char	*dup;

	j = word_len(str, i);
	dup = malloc(sizeof(char) * j + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (str[*i] && str[*i] != '\n' && is_word(str[*i]))
	{
		if (is_quote(str[*i]))
		{
			if (!quote_management(dup, &j, str, i))
				return (free(dup), NULL);			
		}
		else
		{
			dup[j] = str[*i];
			j++;
			(*i)++;			
		}
	}
	dup[j] = '\0';
	return (dup);
}

int	word_management(char *line, int *i, t_token **tk)
{
	t_token *new;

	new = ft_tokennew(NULL);
	if (!new)
		return (0);
	new->type = WORD;
	new->value = copy_word(line, i);
	if (!new->value)
		return (0);
	ft_token_add_back(tk, new);
	return (1);
}

void	print_token(t_token *tk)
{
	while (tk)
	{
		ft_printf("||type is: %d\t", tk->type);
		ft_printf("value is: %s\t|->", tk->value);
		tk = tk->next;
	}
	ft_printf("\n");
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
		{
			if (!opperator_management(line, &i, &tk))
				return ;
		}
		else if (is_redirect(line[i]))
			redirect_management(line, &i, &tk);
		else if (!ft_isspace(line[i]))
		{
			if (!word_management(line, &i, &tk))
				return (ft_tkclear(&tk));			
		}
		else
			i++;
	}
	print_token(tk);
	ft_tkclear(&tk);
}
