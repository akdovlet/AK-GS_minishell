/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:41:40 by akdovlet          #+#    #+#             */
/*   Updated: 2024/07/18 15:44:08 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "token.h"

/*###############################################################################
#                                  tree_utils.c                                 #
###############################################################################*/

t_tree	*tree_node_init(int value);
void	print_tree(t_tree *root);


#endif
