/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:23 by akdovlet          #+#    #+#             */
/*   Updated: 2024/06/27 14:10:59 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ENV_H
# define ENV_H

typedef struct s_env
{
	char	*key;
	char	*value;
	char	*both;
	struct	s_env *next;
}	t_env;

/* env.c */

t_env	*ft_envnew(char *var);
void	ft_add_back(t_env **lst, t_env *new);

//copy the entirety of env into a linked list;
bool	copy_env(t_env **cpy, char **env);

void	env_clear(t_env **lst);

#endif
