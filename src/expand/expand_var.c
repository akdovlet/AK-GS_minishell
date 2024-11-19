/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:37:13 by gschwand          #+#    #+#             */
/*   Updated: 2024/11/19 13:28:19 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "expand.h"

static char	*get_var_value(char *var_name, t_data *data)
{
	char	*value;
	t_env	*node;

	if (!ft_strcmp(var_name, "?"))
	{
		value = ft_itoa(data->status);
		if (!value)
			return (NULL);
		return (value);
	}
	node = env_get_node(data->env, var_name);
	if (!node)
		return (NULL);
	return (node->value);
}

static int	create_and_add_file(char *value, t_files **files)
{
	t_files	*new;

	new = ft_split_to_list(value);
	if (!new)
		return (1);
	files_addback(files, new);
	return (0);
}

int	copy_var(char *str, int *i, t_files **files, t_data *data)
{
	char	*var_name;
	char	*value;
	int		result;

	var_name = extract_var_name(str, i);
	if (!var_name)
		return (1);
	value = get_var_value(var_name, data);
	result = create_and_add_file(value, files);
	return (free(var_name), result);
}

int	check_str_var(char *str)
{
	int	len1;
	int	len2;

	len1 = 0;
	while (str[len1])
		len1++;
	len2 = 1;
	while (str[len2] && (ft_isalnum(str[len2]) || str[len2] == '_'))
		len2++;
	if (len1 != len2)
		return (1);
	return (0);
}

int	check_var(char *str, t_data *data)
{
	int		i;
	char	*var_name;
	t_env	*node;

	i = 0;
	if (!ft_isalpha(str[1]))
		return (0);
	if (check_str_var(str))
		return (0);
	var_name = extract_var_name(str, &i);
	if (!var_name)
		return (1);
	if (!ft_isalpha(var_name[1]))
		return (free(var_name), 0);
	node = env_get_node(data->env, var_name);
	free(var_name);
	if (!node)
		return (1);
	return (0);
}
