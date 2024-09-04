/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_scope.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:02:06 by akdovlet          #+#    #+#             */
/*   Updated: 2024/08/23 15:07:29 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

// static int	scope_recursive(char *str, int *i)
// {
// 	int	error;

// 	while (str[*i] && str[*i] != '\n')
// 	{
// 		if (str[*i] == '(')
// 		{
// 			(*i)++;
// 			error = scope_recursive(str, i);
// 			if (error == 1)
// 				return (1);
// 		}
// 		else if (str[*i] == ')')
// 		{
// 			(*i)++;
// 			return (0);
// 		}
// 		else 
// 			(*i)++;
// 	}
// 	return (1);
// }

// int parenthesis_scope_check(char *str, int *i)
// {
// 	int error;

// 	error = -5;
// 	while (str[*i] && str[*i] != '\n')
// 	{
// 		if (str[*i] == '(')
// 		{
// 			(*i)++;
// 			error = scope_recursive(str, i);
// 		}
// 		else if (str[*i] == ')')
// 			return (2);
// 		else
// 			(*i)++;
// 	}
// 	return (error);
// }
