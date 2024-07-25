/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:23 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/25 18:33:19 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ENV_H
# define ENV_H

typedef struct s_env
{
	char	*key;
	char	*value;
	char	*both;
	struct	s_env *next;
}	t_env;

# include "minishell.h"

// builtins
int		is_builtins(char *cmd);
int		ft_echo(char **args, t_env *env);
int		check_export(char *arg, t_env *env);
int		cd(char **args, t_env *env);
int		ft_pwd(char **args, t_env *env);
void		ft_env(char **args, t_env *env);
int 		ft_export(char **args, t_env *env);
void 		unset(char **tab, t_env *env);
void 		ft_exit(char **tab, t_env *env);


/* env.c */

t_env	*ft_envnew(char *var);
void	ft_add_back(t_env **lst, t_env *new);

//copy the entirety of env into a linked list;
bool	copy_env(t_env **cpy, char **env);

void	env_clear(t_env **lst);

void	print_env(t_env *lst);

// exec
int		ft_exec(char *line, t_env *env);


#endif
