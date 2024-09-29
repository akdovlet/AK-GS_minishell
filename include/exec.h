/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:39:35 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/29 15:29:40 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins.h"
# include "expand.h"

// command_node.c
int	command_node(t_ast *ast, t_data *data);

// command_utils.c
void	clear_exit(t_data *data, int code);
char	*meet_in_the_middle(char *s1, char *s2, char c);
int		hard_path_check(char *cmd);

// exec.c
int exec_recursion(t_ast *ast, t_data *data);

// exec_pipe.c
int			ft_pipe_recursion(t_ast *ast, t_data *data);

// exec_cmd.c
int			ft_is_builtins(char *cmd);
int			ft_builtins(t_ast *ast, t_data *data);

// pidlst.c
t_pidlst	*ft_lstnew_pidlst(pid_t pid);
void	ft_lstadd_back_pidlst(t_pidlst **lst, t_pidlst *new);
void	pidlst_clear(t_pidlst **lst);

int		exec_recursion(t_ast *ast, t_data *data);

// exec_bin.c
int ft_exec_bin(t_ast *ast, t_data *data);
void ft_puterror(char *str_error, char *str);
int ft_find_chr_exec(char *str, char c);

// exec_wait_pid.c
int ft_wait_pid(t_ast *ast, t_data *data);

// operator.c
int ft_operator(t_ast *ast, t_data *data);

// subshell.c
int ft_subshell(t_ast *ast, t_data *data);

// path_utlis.c
void    free_tab_2(char **tab);
void    free_tab(char **tab);
char    *find_path_env(char **env);
char    **find_path_cmd(char **path_env, char *cmd);
char    *find_cmd(char **cmd, char **envp);

//	redir_lst_clear.c
void	fdlst_clear(t_fdlst **lst);
void	fdlst_eat(t_fdlst **node);
void	fdlst_delete_node(t_fdlst **lst, int key);

//	redir_lst.c
t_fdlst	*fdlst_new(int fd, bool close_in_child);
int		fdlst_add_front(t_fdlst	**lst, t_fdlst *new);
void	fdlst_close_in_child(t_fdlst *lst);

//	redir_hd.c
int	redir_hd(t_ast *ast);

//	redir.c
int		redir_node(t_ast *ast, t_data *data);

// execution_loop.c
void	execution_loop(t_data *data);

#endif
