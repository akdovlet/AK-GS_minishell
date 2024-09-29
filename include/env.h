/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:23 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/27 14:39:58 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

// env_cpy.c
int		env_len(t_env *env);
char	**env_copy_to_char_arr(t_env *env);
bool	env_copy(t_env **cpy, char **env);

// env_lst_utils.c
int		find_chr(char *str, char c);
t_env	*ft_last(t_env *lst);
void	env_add_back(t_env **lst, t_env *new);
char	*copy_key(char *str);
t_env	*env_new(char *var);
char *add_dquotes(char *str);
t_env	*export_new(char *var);

// env_setup.c
char	*env_join_keyvalue2(char *key, char *value);
t_env	*env_new_key(char *key, char *value);
bool	env_default_setup(t_data *data);
int		lstdup_env(t_env **dst, t_env *src);

// env_setup2.c
void	ft_sort_alpha(t_env **env);
int		export_default_setup(t_data *data);
int		env_export_default_setup(t_data *data);
int		env_export_copy(t_data *data, char **env);
bool	env_setup(t_data *data, char **env);

// env_utils.c
char	*env_get_value(t_env *env, char *key);
void	env_print(t_env *lst);
void	env_clear(t_env **lst);
t_env	*ft_check_key(t_env **env, char *key);
int		ft_lstsize_env(t_env *lst);

// debug.c
void	print_lst_env(t_env *env);

#endif
