/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:23 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/02 15:15:31 by gschwand         ###   ########.fr       */
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
bool	env_setup(t_data *data, char **env);
int ft_lstsize_env(t_env *lst);

// exec
int		ft_exec(t_ast *line, t_data *data);

t_env *ft_check_key(t_env **env, char *key);


#endif
