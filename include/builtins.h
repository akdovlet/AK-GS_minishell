/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:34:29 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/25 17:52:41 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"

int	ft_echo(char **args, t_env *env);
int	check_export(char *arg, t_data *data);
int	cd(char **args, t_env **env);
int	ft_pwd(char **args, t_env *env);
int	ft_env(char **args, t_env *env);
int	ft_export(char **args, t_data *data);
int	ft_change_value(t_env *node, char *str);
int	check_alnum_str(char *str);
int	unset(char **tab, t_data *data);
int	ft_exit(char **tab, t_env *env, t_data *data);

#endif
