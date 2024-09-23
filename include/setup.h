/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:37:42 by akdovlet          #+#    #+#             */
/*   Updated: 2024/09/23 19:46:16 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SETUP_H
# define SETUP_H

#include "minishell.h"

/*###############################################################################
#                                  setup_shell.c                                #
###############################################################################*/

void	setup_shell(t_data	*data, char	**env);
void	setup_signals(t_data *data);
void	child_handler(int sig);
void	parent_handler(int sig);

#endif
