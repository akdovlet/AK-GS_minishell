/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:23 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/24 18:15:53 by akdovlet         ###   ########.fr       */
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

/* env.c */

t_env	*env_new(char *var);
void	env_add_back(t_env **lst, t_env *new);
//copy the entirety of env into a linked list;
bool	env_copy(t_env **cpy, char **env);
void	env_clear(t_env **lst);
void	env_print(t_env *lst);
bool	env_setup(t_env **my_env, char **env);

#endif
