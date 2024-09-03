/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:39:35 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/03 14:10:35 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins.h"
# include "expand.h"

// exec.c
int exec_recursion(t_ast *ast, t_data *data);

// exec_pipe.c
int			ft_pipe_recusion(t_ast *ast, t_data *data);

// exec_cmd.c
int			ft_is_builtins(char *cmd);
int			ft_builtins(t_ast *ast, t_data *data);

// pidlst.c
t_pidlst	*ft_lstnew_pidlst(pid_t pid);
void	ft_lstadd_back_pidlst(t_pidlst **lst, t_pidlst *new);

// exec_bin.c
int ft_exec_bin(t_ast *ast, t_data *data);
void ft_puterror(char *str_error, char *str);

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

#endif
