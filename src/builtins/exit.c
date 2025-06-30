/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 16:38:28 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/30 11:07:58 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	builtin_exit(t_mshell *shell, char **args)
{
	long	status;

	status = 0;
	if (count_args(args) > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (count_args(args) == 2)
	{
		if (!is_numeric(args[1]))
		{
			print_err("exit\nminishell", args[1], "numeric argument required");
			status = 2;
		}
		else
		{
			status = ft_atoi(args[1]) % 255;
			ft_printf("exit\n");
		}
	}
	ft_free(shell, MEM_TEMP);
	ft_free(shell, MEM_LONG);
	exit(status);
}
