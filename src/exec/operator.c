/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 08:26:48 by gschwand          #+#    #+#             */
/*   Updated: 2024/08/22 08:37:42 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


// penser a remettre data->status a 0 
int ft_operator(t_ast *ast, t_data *data)
{
    data->status = exec_recursion(ast->op_left, data);
    if (ast->cmd[0] == OR && data->status)
        data->status = exec_recursion(ast->op_right, data);
    else if (ast->cmd[0] == AND && !data->status)
        data->status = exec_recursion(ast->op_right, data);
}
