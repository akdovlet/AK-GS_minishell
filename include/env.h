/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:23 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/24 09:12:15 by gschwand         ###   ########.fr       */
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
void		ft_env(t_env *env);
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
