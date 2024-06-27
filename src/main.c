/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/06/27 14:30:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

t_tree	*new_node(char *str)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->value = str;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

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

// int main(int	ac, char **av, char **env)
// {
// 	char	*line;
// 	char	*prompt;
// 	t_token	token;

// 	while (1)
// 	{
// 		line = readline("minishell$");
// 		if (!line)
// 			break ;
// 		free(line);
// 	}
// 	return (0);
// }

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		return (1);
}
