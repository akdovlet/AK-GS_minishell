/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:17:39 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/04 18:31:24 by gschwand         ###   ########.fr       */
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
char **ft_wildcard(char **tab_cmd);

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

// lst_file_utils.c
t_files *ft_recover_files(void);
void ft_free_lst_files(t_files **files);
void ft_lstdelone_files(t_files **files, t_files *to_delete);
t_files *ft_lstnew_files(char *str);
void ft_lst_add_back_files(t_files **alst, t_files *new);

// sort_files.c
// int ft_strcmp_start_end_wildcard(char *file, char *str);
int ft_strcmp_end_start_wildcard(char *file, char *str);
void ft_lstcomp_wildcard(t_files **files, char *str);
// void ft_lstcomp_wildcard(t_files **files, char *str, int (*strcmp)(char*, char*));
void ft_strlcat_files(char *dst, const char *src, size_t lenres);
char *write_files(t_files *files);



#endif