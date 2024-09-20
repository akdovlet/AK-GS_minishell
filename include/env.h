/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:23 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/20 14:45:12 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ENV_H
# define ENV_H

# include "minishell.h"

/* env.c */

char	*env_get_value(t_env *env, char *key);
char	**env_copy_to_char_arr(t_env *env);
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
