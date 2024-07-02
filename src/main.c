/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/02 18:01:32 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"


// Premiere fonction: retourner list chainee avec dans chaque noeud une string,
// et un operateur. Attention aux parentheses a gerer comme un bloc. 
// echo a | grep a && echo c
// char	**token_split(char *str)
// {
// 	int		i;
// 	int		wordcount;
// 	char	**splitter;

// 	i = 0;
// 	wordcount = token_count(str);
// }


// char	*pre_prompt(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp("USER=", env[i], 5))
// 		{
			
// 		}
// 	}
// }

void	opperator_management(char *str, int *i, t_token **tk)
{

}

void	tokenize(char *line)
{
	int	i;
	int	start;
	int	end;
	t_token	*tk;

	i = 0;
	while (line[i])
	{
		if (is_opperator(line[i]))
			opperator_management(line, &i, &tk);
		if (is_quotes(line[i]))
			quotes_management(line, &i);
		if (!ft_isspace(line[i]))
			word_management(line, &i, &tk);
		i++;
	}
}


// IFS bash
// bash-5.1$ export B='"   salut comment ca va   "'
// bash-5.1$ echo $B
// " salut comment ca va "
// in env: 
// B="   salut comment ca va   "
/*
bash-5.1$ export B=Yo comment ca va
bash-5.1$ echo $B
Yo
bash-5.1$ export B=(Yo comment ca va)
bash-5.1$ echo $B
Yo

*/
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*line;

	while (1)
	{
		line = readline("minishell$> ");
		if (!line)
			break ;
		// tokenize(line);
		free(line);
	}
	return (0);
}
