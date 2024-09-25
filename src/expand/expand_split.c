/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:35:52 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/25 12:40:16 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

// static int	ft_sep(char c, char *sep)
// {
// 	int	i;

// 	i = 0;
// 	if (sep == NULL)
// 		return (0);
// 	while (sep[i])
// 	{
// 		if (c == sep[i])
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// static char	*ft_strdup_split_e(char *str, int index, int nbchar)
// {
// 	int		i;
// 	char	*copy;

// 	i = 0;
// 	copy = malloc((nbchar + 1) * sizeof(char));
// 	if (copy == NULL)
// 		return (0);
// 	if (index < 0)
// 		index = 0;
// 	while (i < nbchar)
// 	{
// 		copy[i] = str[index + i];
// 		i++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }

// static int	ft_count_char_and_alloc_expand(char *str, char *charsep, char **tab)
// {
// 	int	m;
// 	int	nbchar;
// 	int	i;

// 	i = 0;
// 	m = 0;
// 	nbchar = 0;
// 	while (i == 0 || str[i - 1])
// 	{
// 		if (str[i] && ft_sep(str[i], charsep) == 0)
// 			nbchar++;
// 		else
// 		{
// 			nbchar++;
// 			tab[m] = ft_strdup_split_e(str, i - nbchar, nbchar);
// 			if (tab[m] == NULL)
// 				return (0);
// 			m++;
// 			nbchar = 0;
// 		}
// 		i++;
// 	}
// 	return (m);
// }

// static int	ft_count_word(char *str, char *charsep)
// {
// 	int	m;
// 	int	nbchar;
// 	int	i;

// 	i = 0;
// 	m = 0;
// 	nbchar = 0;
// 	while (i == 0 || str[i - 1])
// 	{
// 		if (str[i] && ft_sep(str[i], charsep) == 0)
// 			nbchar++;
// 		else
// 		{
// 			m++;
// 			nbchar = 0;
// 		}
// 		i++;
// 	}
// 	return (m);
// }


// split qui renvoie une liste chainee de t_files
// separe en fonction des whitespaces
// ne se fait que dans l'expand de variables
// et que lorsque celui ci a deja ete fait
// t_files	*ft_split_var_files(char *str)
// {
// 	char	**tab;
// 	int		nbword;

// 	if (str == NULL || str[0] == '\0')
// 		nbword = 0;
// 	else
// 		nbword = ft_count_word(str);
// 	tab = malloc((nbword + 1) * sizeof(char *));
// 	if (tab == NULL)
// 		return (NULL);
// 	if (nbword > 0)
// 		ft_count_char_and_alloc_expand(str, sep, tab);
// 	tab[nbword] = 0;
// 	return (tab);
// }


// --------------------------------------

static int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

t_files *create_new_file_node(char *name)
{
    t_files *new_node;

    new_node = (t_files *)malloc(sizeof(t_files));
    if (!new_node)
        return NULL;
    new_node->name = name;
    new_node->next = NULL;
    return new_node;
}

// Ajout d'un élément à la fin de la liste
void add_file_node(t_files **head, t_files *new_node)
{
    t_files *temp;

    if (!*head)
    {
        *head = new_node;
        return;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
}

// Fonction pour découper la chaîne et créer la liste chaînée
t_files *ft_split_to_list(char *str)
{
    t_files *head = NULL;
    char *start;
    char *word;

    while (*str)
    {
        // Ignorer les espaces blancs initiaux
        while (*str && ft_whitespace(*str))
            str++;
        if (*str)
        {
            // Définir le début du mot
            start = str;
            // Trouver la fin du mot
            while (*str && !ft_whitespace(*str))
                str++;
            // Dupliquer le mot et créer un nouveau nœud
            word = strndup(start, str - start);
            if (!word)
            {
                // En cas d'erreur de mémoire, on peut libérer la liste ici
                return NULL;
            }
            add_file_node(&head, create_new_file_node(word));
        }
    }
    return head;
}
