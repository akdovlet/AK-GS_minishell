/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:37:13 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/02 14:16:28 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

// size_t	ft_strlen_expand(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	if (s)
// 	{
// 		while (s[i] && s[i] != '\'' && s[i] != '\"')
// 			i++;
// 	}
// 	return (i);
// }

void free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

size_t ft_strlen_tab(char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}


// fonction qui concataine toutes les lignes d'un tableau
char *ft_cat_tab(char **str)
{
    int i;
    int lenres;
    char *res;
    
    i = 0;
    lenres = 0;
    while (str[i])
    {
        lenres += ft_strlen_tab(str[i]);
        i++;
    }
    res = malloc(sizeof(char) * (lenres + 1));
    if (!res)
        return (NULL);
    i = 1;
    ft_strlcpy(res, str[0], ft_strlen_tab(str[0]));
    printf("res = %s\n", res);
    while (str[i])
    {
        if (i == 2)
        {
            printf("---------\nstr[i] = %s\n---------\n", str[i]);
        }
        ft_strlcat(res, str[i], ft_strlen_tab(str[i]));
        printf("%der res = '%s'\n", i, res);
        i++;
    }
    return (res);
}

static t_env *ft_check_key_expand(t_env *env, char *key)
{
    t_env *tmp;
    
    tmp = env;
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, key))
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

char *expand_var(char *str, t_env *env)
{
    t_env *node;
    char *res;
    char **tmp;
    int i;

    i = 0;
    res = NULL;
    tmp = ft_split_expand(str, "$ \'\"");
    if (!tmp)
        return (NULL);
    free(str);
    while (tmp[i])
    {
        if (tmp[i][0] == '$')
        {
            node = ft_check_key_expand(env, tmp[i] + 1);
            free(tmp[i]);
            if (!node)
                tmp[i] = NULL;
            else
                tmp[i] = node->value;
        }
        i++;
    }
    print_tab(tmp);
    res = ft_cat_tab(tmp);
    return (res);   
}
