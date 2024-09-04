/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 08:26:48 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/03 11:37:38 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


// penser a remettre data->status a 0 
int ft_operator(t_ast *ast, t_data *data)
{
    data->status = exec_recursion(ast->op_left, data);
    if (ast->op_type == OR && data->status)
        data->status = exec_recursion(ast->op_right, data);
    else if (ast->op_type == AND && !data->status)
        data->status = exec_recursion(ast->op_right, data);
    return (0);
}
