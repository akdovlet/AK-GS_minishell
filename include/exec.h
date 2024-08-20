/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:39:35 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/20 17:09:16 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins.h"

// exec_pipe.c
int ft_pipe_recusion(t_ast *ast, t_data *data);

// exec_cmd.c
int ft_is_builtins(char *cmd);
int ft_builtins(t_ast *ast, t_data *data)

// pidlst.c
t_pidlst	*ft_lstnew_pidlst(pid_t pid);
void	ft_lstadd_back_pidlst(t_pidlst **lst, t_pidlst *new);

#endif