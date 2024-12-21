/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:34:29 by gschwand          #+#    #+#             */
/*   Updated: 2024/12/21 15:07:56 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"

# define PWDERROR "minishell: pwd: error retrieving current directory: getcwd:\
 cannot access parent directories"

int		builtin_echo(char **strs);
int		builtin_cd(t_data *data, char **args, t_env **env);
int		check_export(char *arg, t_data *data);
int		ft_pwd(char **args, t_env *env);
int		ft_env(char **args, t_env *env);
int		ft_export(char **args, t_data *data);
int		ft_change_value(t_env *node, char *str);
int		check_alnum_str(char *str);
int		unset(char **tab, t_data *data);
int		ft_exit(char **tab, t_data *data);
int		check_overflow(char *str, int n);
char	*remove_quotes(char *str);

#endif
