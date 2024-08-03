/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:34:29 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/01 15:13:12 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"

int 		ft_echo(char **args, t_env *env);
int 		check_export(char *arg, t_env *env);
int 		cd(char **args, t_env *env);
int 		ft_pwd(char **args, t_env *env);
void		ft_env(char **args, t_env *env);
int 		ft_export(char **args, t_env *env);
void 		unset(char **tab, t_env *env);
void 		ft_exit(char **tab, t_env *env);

#endif
