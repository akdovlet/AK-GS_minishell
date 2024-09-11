/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 08:26:48 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/11 17:00:34 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


// penser a remettre data->status a 0 
int ft_operator(t_ast *ast, t_data *data)
{
    printf("ft_operator\n");
    exec_recursion(ast->op_left, data);
    printf("data->status = %d\n", data->status);
    if (ast->op_type == OR && data->status)
        exec_recursion(ast->op_right, data);
    else if (ast->op_type == AND && !data->status)
    {
        printf("data->status = %d\n", data->status);
        exec_recursion(ast->op_right, data);
    }
    return (0);
}
