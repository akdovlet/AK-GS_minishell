/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:17:39 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/05 17:04:38 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

#include "minishell.h"
#include "env.h"

typedef struct s_files
{
    char *name;
    struct s_files *next;
}               t_files;

// wildcard.c
int ft_wildcard(char **tab_cmd);

// expand_var.c
char *expand_var(char *str, t_env *env);
int expand_tab_of_cmd(char **tab_cmd, t_env *env);

// expand_quotes_utils.c
int ft_find_chr(char *str, char c);
int ft_strlen_wo_c(const char *str, char c);
void ft_strlcpy_wo_c(char *dst, const char *src, char c);

// expand_split.c
char **ft_split_expand(char *str, char *sep);


// expand_debugg.c
void print_tab(char **tab);
void ft_print_lst_files(t_files *files);


#endif