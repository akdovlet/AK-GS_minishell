/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/11 13:25:10 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "token.h"

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
%echo >outfile word
%cat outfile
%word

bash-5.1$ "ls -la"
bash: ls -la: command not found
*/

int main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_env	*my_env;

	if (ac != 1)
		return (1);
	my_env = NULL;
	copy_env(&my_env, env);
	print_env(my_env);
	while (1)
	{
		line = readline(CYAN "minishell$> " RESET);
		if (!line)
			break ;
		add_history(line);
		tokenize(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
