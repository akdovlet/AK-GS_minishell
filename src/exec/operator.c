/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 08:26:48 by gschwand          #+#    #+#             */
/*   Updated: 2024/09/26 18:51:21 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// penser a remettre data->status a 0 
int	ft_operator(t_ast *ast, t_data *data)
{
	exec_recursion(ast->op_left, data);
	if (ast->op_type == OR && data->status)
		data->status = exec_recursion(ast->op_right, data);
	else if (ast->op_type == AND && !data->status)
		data->status = exec_recursion(ast->op_right, data);
	return (data->status);
}
