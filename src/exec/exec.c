/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:38:30 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/22 13:54:39 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

// need correction for cd's call
// int ft_exec(t_token *tk, t_env *env)
// {
//     while (tk)
//     {
//         (void)env;
//         if (tk->type == BUILTIN)
//         {
//             // if (!ft_strcmp(tk->value, "echo"))
//             //     echo(tk->next->value);
//             if (!ft_strcmp(tk->value, "cd"))
//                 cd(tk->next->value);
//             else if (!ft_strcmp(tk->value, "pwd"))
//                 ft_pwd();
//             // else if (!ft_strcmp(tk->value, "export"))
//             //     export(tk->next->value, env);
//             // else if (!ft_strcmp(tk->value, "unset"))
//             //     unset(tk->next->value, env);
//             // else if (!ft_strcmp(tk->value, "env"))
//             //     env_(env);
//             // else if (!ft_strcmp(tk->value, "exit"))
//             //     exit_(tk->next->value);
//         }
//         tk = tk->next;
//     }
//     return (0);
// }
