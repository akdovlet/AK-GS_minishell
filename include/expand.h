/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:17:39 by gschwand          #+#    #+#             */
/*   Updated: 2024/10/29 16:49:20 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "minishell.h"

typedef struct s_files
{
	char			*name;
	struct s_files	*next;
}					t_files;

// expand.c
char				**expand_tab_of_cmd(char **tab_cmd, t_data *data);
int					expand_str(char *str, t_data *data, t_files **files);

// expand_var.c
int					copy_var(char *str, int *i, t_files **files, t_data *data);
int					check_var(char *str, t_data *data);

// expand_quotes_utils.c
int					ft_find_chr(char *str, char c);

// expand_split.c
// char				**ft_split_expand(char *str, char *sep);
t_files				*ft_split_to_list(char *str);

// expand_debugg.c
void				print_tab(char **tab);
void				ft_print_lst_files(t_files *files);

// lst_file_utils.c
t_files				*files_new(char *str);
t_files				*files_new_dup(char *str);
void				ft_lstdelone_files(t_files **files, t_files *to_delete);
int					files_add_back_new(t_files **alst, t_files *new);
void				files_add_back(t_files **alst, t_files *new);

// lst_file_utils2.c
void				ft_free_lst_files(t_files **files);
void				ft_free_lst_files_expand(t_files **files);
t_files				*ft_recover_files(void);
char				*write_files_expand(t_files *files);
int					creat_node_n_add_back_if_str(t_files **files, char *str);

// lst_file_utils3.c
int					creat_node_n_add_back(t_files **files, char *str);
int					lst_size_files(t_files **files);
char				**ft_lst_to_tab(t_files **files);
char				*write_files(t_files *files);
void				ft_sort_alpha_files(t_files **files);

// sort_files.c
int					ft_strcmp_end_start_wildcard(char *file, char *str);
void				ft_lstcomp_wildcard(t_files **files, char *str);
void				ft_strlcat_files(char *dst, const char *src, size_t lenres);

// wildcard.c
char				**ft_wildcard(char **tab_cmd);
t_files				*expand_wildcard(t_files **files, char *str);
void				free_tab(char **tab);

// wildcard_utils.c
int					ft_strcasecmp(char *s1, char *s2);

// expand_first_cmd.c
char				**expand_first_cmd(char **tab_cmd, t_data *data);

// expand_first_cmd2.c
t_files				*tab_to_lst_files(t_files **files, char **tab);
char				**strdup_tab(char **tab);

// wildcard_first_cmd.c
char				**ft_wildcard_first_cmd(char **cmd);
int					ft_find_chr_exec(char *str, char c);

// expand_files.c
void				dq_copy(char *str, int *i, t_data *data, t_files **lst);
char				*expand_filename(char *str, t_data *data);
void				files_clear(t_files **head);
char				*files_join(t_files **lst);
void				var_copy(char *str, int *i, t_data *data, t_files **lst);
void				status_copy(int *i, t_data *data, t_files **head);
char				*line_expand(char *line, t_env *env);
#endif
