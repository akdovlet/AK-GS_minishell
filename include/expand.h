/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:17:39 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/24 13:44:43 by gschwand         ###   ########.fr       */
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

// expand.c
char **expand_tab_of_cmd(char **tab_cmd, t_data *data);

// wildcard.c
char **ft_wildcard(char **tab_cmd);
void free_tab(char **tab);

// expand_var.c
int copy_var(char *str, int *i, t_files **files, t_data *data);
int check_var(char *str, t_data *data);

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
t_files *ft_lstnew_files_dup(char *str); 
int ft_new_lst_add_back_files(t_files **alst, t_files *new);
void ft_lst_add_back_files(t_files **alst, t_files *new);
void ft_free_lst_files_expand(t_files **files);
char *write_files_expand(t_files *files);
int creat_node_n_add_back_if_str(t_files **files, char *str);
int creat_node_n_add_back(t_files **files, char *str);
int lst_size_files(t_files **files);


// sort_files.c
// int ft_strcmp_start_end_wildcard(char *file, char *str);
int ft_strcmp_end_start_wildcard(char *file, char *str);
void ft_lstcomp_wildcard(t_files **files, char *str);
// void ft_lstcomp_wildcard(t_files **files, char *str, int (*strcmp)(char*, char*));
void ft_strlcat_files(char *dst, const char *src, size_t lenres);
char *write_files(t_files *files);



#endif
