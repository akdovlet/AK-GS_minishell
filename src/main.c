/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/25 12:36:15 by gautier          ###   ########.fr       */
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

bash-5.1$ print $USER
bash: print: command not found
bash-5.1$ print $USER
bash: print: command not found
bash-5.1$ echo $"USER"
USER
bash-5.1$ echo 12$USER
12akdovletov
bash-5.1$ echo 12$"USER"
12USER

$ with numeric after is not var env, not to do


Bash is the shell, or command language interpreter, for the GNU operating system. 
The name is an acronym for the ‘Bourne-Again SHell’, a pun on Stephen Bourne, 
the author of the direct ancestor of the current Unix shell sh, which appeared in the
 Seventh Edition Bell Labs Research version of Unix. 

Shells also provide a small set of built-in commands (builtins) 
implementing functionality impossible or inconvenient to obtain
via separate utilities. For example, cd, break, continue, and 
exec cannot be implemented outside of the shell because they directly
manipulate the shell itself. The history, getopts, kill, or pwd builtins,
among others, could be implemented in separate utilities, but they are more
convenient to use as builtin commands. All of the shell builtins are described
in subsequent sections. 

//check les redirs avec plusieurs in: < in < in2 < in3
pareil avc les out et le heredoc

singaux avec sigactions

si pipeline tout est dans l'enfant
signaux ctrlc ne doit pas quitter le programme

*/

int main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_env	*my_env;
	t_token	*tk;

	if (ac != 1)
		return (1);
	my_env = NULL;
	tk = NULL;
	copy_env(&my_env, env);
	if (!env[0])
		printf("empty\n");
	// print_env(my_env);
	while (1)
	{
		line = readline(CYAN "minishell$> " RESET);
		if (!line)
			break ;
		add_history(line);
		tokenize(line, &tk);
		ft_exec(line, my_env);
		free(line);
		ft_tkclear(&tk);
	}
	env_clear(&my_env);
	rl_clear_history();
	return (0);
}
