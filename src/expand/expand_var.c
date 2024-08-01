/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:37:13 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/01 09:02:42 by gschwand         ###   ########.fr       */
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

static t_env *ft_check_key_expand(t_env *env, char *key)
{
    t_env *tmp;
    
    tmp = env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key + ft_find_chr(key, '$') + 1, ft_strlen_expand(tmp->key)))
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

// probleme j'ai oublie de supp la key 
char *ft_add_var(char *str, char *value, char *key)
{
    char *res;
    int lenres;

    
    lenres = ft_strlen(str) + ft_strlen(value) - 1;
    res = malloc(sizeof(char) * (lenres + 1));
    if (!res)
        return (NULL);
    ft_strlcpy(res, str, ft_find_chr(str, '$'));
    ft_strlcat(res, value, lenres + 1);
    ft_strlcat(res, str + ft_find_chr(str, '$') + 1 + , lenres + 1);
    return (res);
}

static int ft_strlen_no_quotes(const char *s)
{
    int i;
    int quote;
    int dquote;

    i = 0;
    quote = 0;
    dquote = 0;
    while (s[i])
    {
        if (s[i] == '\'')
            quote += 1;
        else if (s[i] == '\"')
            dquote += 1;
        i++;
    }
    return (i - quote - dquote);
}

static void ft_strlcpy_no_quotes(char *dst, const char *src)
{
    int i;
    int j;
    int quote;
    int dquote;

    i = 0;
    j = 0;
    quote = 0;
    dquote = 0;
    while (src[i])
    {
        if (src[i] == '\'')
            quote += 1;
        else if (src[i] == '\"')
            dquote += 1;
        else
        {
            dst[j] = src[i];
            j++;
        }
        i++;
    }
    dst[j] = '\0';
}

char *ft_supp_quotes(char *str)
{
    char *res;
    int lenres;

    lenres = ft_strlen_no_quotes(str);
    res = malloc(sizeof(char) * (lenres + 1));
    if (!res)
        return (NULL);
    ft_strlcpy_no_quotes(res, str);
    free(str);
    return (res);
}

// renvoyer une string sans ' et "
char *expand_var(char *str, t_env *env)
{
    t_env *node;
    char *res;

    printf("ok\n");
    node = ft_check_key_expand(env, str + ft_find_chr(str, '$'));
    if (!node)
        res = ft_strndup(str, ft_find_chr(str, '$') - 1);
    else
        res = ft_add_var(str, node->value, node->key);
    res = ft_supp_quotes(res);
    free(str);
    return (res);
}