/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:23 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/31 18:48:11 by gschwand         ###   ########.fr       */
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

/* env.c */

t_env	*ft_envnew(char *var);
void	ft_add_back(t_env **lst, t_env *new);

//copy the entirety of env into a linked list;
bool	copy_env(t_env **cpy, char **env);

void	env_clear(t_env **lst);

void	print_env(t_env *lst);

// exec
int		ft_exec(char *line, t_env *env);

t_env *ft_check_key(t_env **env, char *key);


#endif
