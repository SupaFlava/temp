/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:07:34 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/24 18:47:09 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// builtin_echo(shell, (char *[]){"echo", "-n", "hello", "world", NULL});

int	builtin_echo(t_mshell *shell, char **args)
{
	int	i;
	int	flag;

	(void)shell;
	flag = 0;
	i = 1;
	if (!args[1])
	{
		return (ft_putchar_fd('\n', STDOUT_FILENO), 0);
	}
	if (ft_strlen(args[1]) == 2 && ft_strncmp(args[1], "-n", 2) == 0)
	{
		flag = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i] == NULL && flag == 0)
			ft_putchar_fd('\n', STDOUT_FILENO);
		else if (args[i] == NULL && flag == 0)
			break ;
		else if (args[i] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	return (0);
}
