/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:37:13 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/31 20:10:51 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int ft_find_chr(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}

size_t	ft_strlen_expand(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i] && s[i] != '\'' && s[i] != '\"')
			i++;
	}
	return (i);
}

static t_env *ft_check_key_expand(t_env **env, char *key)
{
    t_env *tmp;
    
    tmp = *env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, ft_strlen_expand(tmp->key)))
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

char *ft_add_var(char *str, char *value)
{
    char *res;
    int lenres;

    
}

// renvoyer une string sans ' et "
char *expand_var(char *str, t_env *env)
{
    t_env *node;
    char *res;

    node = ft_check_key(env, ft_find_chr(str, '$'));
    if (!node)
        res = ft_strndup(str, ft_find_chr(str, '$') - 1);
    else
        res = ft_add_var(str, node->value);
    res = ft_supp_quotes(res);
    free(str);
    return (res);
    
}