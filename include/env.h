/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:23 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/20 17:48:41 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ENV_H
# define ENV_H

# include "minishell.h"

/* env.c */

t_env	*env_new(char *var);
void	env_add_back(t_env **lst, t_env *new);
//copy the entirety of env into a linked list;
bool	env_copy(t_env **cpy, char **env);
void	env_clear(t_env **lst);
void	env_print(t_env *lst);
bool	env_setup(t_env **my_env, char **env);
int ft_lstsize_env(t_env *lst);



#endif
