/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:39:46 by gschwand          #+#    #+#             */
/*   Updated: 2024/06/19 19:29:44 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_parenthesis(char *prompt)
{
    int i;
    int j;

    i = 0;
    j = 1;
    while (prompt[i] && j > 0)
    {
        if (prompt[i] == '(')
            j++;
        if (prompt[i] == ')')
            j--;
        i++;
    }
    return (i);
}

int strcpy_prompt_tree(char *prompt, char **str)
{
    int i;
    int j;

    i = 0;
    while (prompt[i] == ' ')
        i++;
    if (prompt[i] == '(')
        j = find_parenthesis(prompt + i);
    else
        j = find_operator(prompt + i);
    *str = ft_strndup(prompt + i, j);
    return (i);
}

void alloc_tree(t_tree **tree, char *prompt)
{
    t_tree *node;
    char *str;
    int i;

    i = strcpy_prompt_tree(prompt + i, &str);
    ft_printf ("str = %s\n", str);
    node = lstnew()
}

t_tree **init_tree(char *prompt)
{
    t_tree **tree;
    t_tree *node;
    
    tree = malloc(sizeof(t_tree *));
    if (!tree)
    {
        perror("malloc");
        return (NULL);
    }
    *tree = NULL;
    alloc_tree(tree, prompt);
    return (tree);
}
