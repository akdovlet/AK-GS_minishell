/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:11 by akdovlet          #+#    #+#             */
/*   Updated: 2024/06/20 12:32:38 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *prompt = "";
	t_tree 		**tree;
	
	tree = init_tree(prompt);
	return (0);
}


int searchNode (node*tree, unsigned int key)
{
	while(tree)
	{
		if(key== tree->key)
			return (1);
		if(key> tree->key ) 
			tree= tree->right;
		else 
			tree= tree->left;
	}
	return (0);
}