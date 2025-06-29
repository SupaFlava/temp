/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 16:07:34 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/29 20:01:38 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_flag(char *arg)
{
	size_t i;
	size_t len;

	i = 1;
	len = ft_strlen(arg);
	if (arg[0] == '-')
	{
		while(arg[i])
		{
			if(arg[i] == 'n')
				i++;
			else
			break ;
		}
		if (i != len)
			return (0);
		else
		return (1);
	}
	return (0);
}

int	builtin_echo(t_mshell *shell, char **args)
{
	int	i;
	int	flag;

	(void)shell;
	flag = 0;
	i = 1;
	if (!args[1])
		return (ft_putchar_fd('\n', STDOUT_FILENO), 0);
	while (args[i] && check_flag(args[i]))
	{
		flag = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}