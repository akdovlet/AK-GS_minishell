/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:05:02 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/03 11:13:54 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int cd(char *args)
{
    if (args == NULL)
    {
        ft_putstr_fd("minishell: expected argument to \"cd\"\n", STDERR_FILENO);
    }
    else
    {
        if (chdir(args) != 0)
        {
            perror("minishell");
        }
    }
    return (0);
}

int main(int ac, char **av)
{
    cd(av[1]);
}